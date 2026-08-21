// Copyright (c) 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/traffic_control/traffic_control_apply.h"

#include <string>
#include <utility>

#include "base/logging.h"
#include "brave/browser/containers/containers_service_factory.h"
#include "brave/browser/traffic_control/traffic_control_tab_utils.h"
#include "brave/components/containers/content/browser/storage_partition_utils.h"
#include "brave/components/containers/core/browser/containers_service.h"
#include "brave/components/containers/core/mojom/containers.mojom.h"
#include "brave/components/traffic_control/core/mojom/traffic_control.mojom.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"
#include "chrome/browser/ui/navigator/browser_navigator.h"
#include "chrome/browser/ui/navigator/browser_navigator_params.h"
#include "chrome/browser/ui/tabs/tab_enums.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "components/tabs/public/tab_interface.h"
#include "content/public/browser/storage_partition_config.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/page_transition_types.h"
#include "ui/base/window_open_disposition.h"

namespace traffic_control {

namespace {

void OpenUrlWithOptionalContainer(
    BrowserWindowInterface* browser_window,
    const GURL& url,
    const containers::mojom::ContainerPtr& container) {
  NavigateParams params(browser_window, url, ui::PAGE_TRANSITION_LINK);
  params.disposition = WindowOpenDisposition::NEW_FOREGROUND_TAB;
  if (container) {
    params.storage_partition_config = content::StoragePartitionConfig::Create(
        browser_window->GetProfile(),
        containers::kContainersStoragePartitionDomain, container->id,
        browser_window->GetProfile()->IsOffTheRecord());
  }
  Navigate(&params);
}

}  // namespace

void ApplyTrafficControlTarget(content::WebContents* source,
                               const GURL& url,
                               const mojom::TargetPtr& target) {
  if (!source || !target || !url.is_valid()) {
    return;
  }

  tabs::TabInterface* source_tab =
      tabs::TabInterface::MaybeGetFromContents(source);
  if (!source_tab) {
    LOG(ERROR) << "Traffic Control: source tab not found";
    return;
  }

  BrowserWindowInterface* browser_window =
      source_tab->GetBrowserWindowInterface();
  if (!browser_window) {
    LOG(ERROR) << "Traffic Control: browser window not found";
    return;
  }

  Profile* profile = browser_window->GetProfile();
  const bool close_source_after = IsDiscardableEmptyTab(source);
  TabStripModel* tab_strip = browser_window->GetTabStripModel();

  if (target->temporary_container) {
    auto* containers_service = ContainersServiceFactory::GetForProfile(profile);
    if (!containers_service) {
      LOG(ERROR) << "Traffic Control: ContainersService unavailable";
      return;
    }
    OpenUrlWithOptionalContainer(
        browser_window, url,
        containers_service->CreateAndPersistTemporaryContainer());
  } else if (target->container_id.has_value()) {
    if (target->container_id->empty()) {
      OpenUrlWithOptionalContainer(browser_window, url, nullptr);
    } else {
      auto* containers_service =
          ContainersServiceFactory::GetForProfile(profile);
      if (!containers_service) {
        LOG(ERROR) << "Traffic Control: ContainersService unavailable";
        return;
      }
      auto container =
          containers_service->GetRuntimeContainerById(*target->container_id);
      if (!container) {
        LOG(ERROR) << "Traffic Control: unknown container id "
                   << *target->container_id;
        return;
      }
      OpenUrlWithOptionalContainer(browser_window, url, container);
    }
  } else {
    return;
  }

  if (!close_source_after || !tab_strip) {
    return;
  }

  // Re-resolve by pointer; indices can shift when the new tab is inserted.
  const int source_index_after = tab_strip->GetIndexOfWebContents(source);
  if (source_index_after != TabStripModel::kNoTab) {
    tab_strip->CloseWebContentsAt(source_index_after,
                                  TabCloseTypes::CLOSE_NONE);
  }
}

}  // namespace traffic_control
