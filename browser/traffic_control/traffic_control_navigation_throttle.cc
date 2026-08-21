// Copyright (c) 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/traffic_control/traffic_control_navigation_throttle.h"

#include <string>
#include <utility>

#include "base/functional/bind.h"
#include "base/logging.h"
#include "base/memory/weak_ptr.h"
#include "base/task/sequenced_task_runner.h"
#include "brave/browser/containers/containers_service_factory.h"
#include "brave/browser/traffic_control/traffic_control_apply.h"
#include "brave/browser/traffic_control/traffic_control_tab_utils.h"
#include "brave/components/containers/content/browser/preserve_container_destination.h"
#include "brave/components/containers/content/browser/storage_partition_utils.h"
#include "brave/components/containers/core/browser/containers_service.h"
#include "brave/components/containers/core/browser/temporary_container.h"
#include "brave/components/containers/core/mojom/containers.mojom.h"
#include "brave/components/traffic_control/core/browser/traffic_control_service.h"
#include "brave/components/traffic_control/core/mojom/traffic_control.mojom.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle_registry.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/page_transition_types.h"
#include "url/gurl.h"

namespace traffic_control {

namespace {

bool AlreadyAtTarget(content::WebContents* web_contents,
                     const mojom::TargetPtr& target) {
  if (!web_contents || !target) {
    return false;
  }

  // Temporary destinations always open a new tab from non-temporary sources.
  // Once already in a temporary container, proceed to avoid an apply loop on
  // the newly opened tab's navigation.
  if (target->temporary_container) {
    return containers::IsTemporaryContainerId(
        containers::GetContainerIdForWebContents(web_contents));
  }

  if (!target->container_id.has_value()) {
    return false;
  }

  const std::string current =
      containers::GetContainerIdForWebContents(web_contents);
  if (target->container_id->empty()) {
    // Non-contained destination: already there if not in a container.
    return current.empty();
  }
  return current == *target->container_id;
}

}  // namespace

// static
void TrafficControlNavigationThrottle::MaybeCreateAndAdd(
    content::NavigationThrottleRegistry& registry,
    TrafficControlService* service) {
  if (!service || !service->IsEnabled()) {
    return;
  }

  registry.AddThrottle(
      std::make_unique<TrafficControlNavigationThrottle>(registry, *service));
}

TrafficControlNavigationThrottle::TrafficControlNavigationThrottle(
    content::NavigationThrottleRegistry& registry,
    TrafficControlService& service)
    : content::NavigationThrottle(registry), service_(service) {}

TrafficControlNavigationThrottle::~TrafficControlNavigationThrottle() = default;

content::NavigationThrottle::ThrottleCheckResult
TrafficControlNavigationThrottle::WillStartRequest() {
  return MaybeReroute();
}

content::NavigationThrottle::ThrottleCheckResult
TrafficControlNavigationThrottle::WillRedirectRequest() {
  return MaybeReroute();
}

content::NavigationThrottle::ThrottleCheckResult
TrafficControlNavigationThrottle::MaybeReroute() {
  content::NavigationHandle* handle = navigation_handle();
  content::WebContents* web_contents = handle->GetWebContents();
  if (!web_contents || !handle->IsInMainFrame()) {
    return PROCEED;
  }
  if (handle->IsSameDocument() || handle->IsDownload()) {
    return PROCEED;
  }

  // Explicit container UI (NavigateParams::preserve_container_destination).
  if (containers::PreserveContainerDestination::Consume(web_contents)) {
    return PROCEED;
  }

  mojom::TrafficRulePtr rule = service_->FindMatchingRule(handle->GetURL());
  if (!rule || !rule->target) {
    return PROCEED;
  }

  // Soft-fail unset destinations.
  if (!rule->target->temporary_container &&
      !rule->target->container_id.has_value()) {
    return PROCEED;
  }

  if (AlreadyAtTarget(web_contents, rule->target)) {
    return PROCEED;
  }

  // Same schemeful site stays put unless this is an omnibox navigation.
  if (!IsOmniboxNavigation(handle->GetPageTransition()) &&
      !CrossesSchemefulSiteBoundary(web_contents->GetLastCommittedURL(),
                                    handle->GetURL())) {
    return PROCEED;
  }

  // Unknown container id: soft-fail without canceling.
  if (!rule->target->temporary_container &&
      rule->target->container_id.has_value() &&
      !rule->target->container_id->empty()) {
    Profile* profile =
        Profile::FromBrowserContext(web_contents->GetBrowserContext());
    auto* containers_service = ContainersServiceFactory::GetForProfile(profile);
    if (!containers_service || !containers_service->GetRuntimeContainerById(
                                   *rule->target->container_id)) {
      LOG(ERROR) << "Traffic Control: unknown container id "
                 << *rule->target->container_id;
      return PROCEED;
    }
  }

  const GURL url = handle->GetURL();
  mojom::TargetPtr target = rule->target->Clone();

  base::SequencedTaskRunner::GetCurrentDefault()->PostTask(
      FROM_HERE, base::BindOnce(
                     [](base::WeakPtr<content::WebContents> web_contents,
                        GURL url, mojom::TargetPtr target) {
                       if (!web_contents) {
                         return;
                       }
                       ApplyTrafficControlTarget(web_contents.get(), url,
                                                 target);
                     },
                     web_contents->GetWeakPtr(), url, std::move(target)));

  return CANCEL;
}

const char* TrafficControlNavigationThrottle::GetNameForLogging() {
  return "TrafficControlNavigationThrottle";
}

}  // namespace traffic_control
