// Copyright (c) 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_TRAFFIC_CONTROL_TRAFFIC_CONTROL_APPLY_H_
#define BRAVE_BROWSER_TRAFFIC_CONTROL_TRAFFIC_CONTROL_APPLY_H_

#include "brave/components/traffic_control/core/mojom/traffic_control.mojom-forward.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}  // namespace content

namespace traffic_control {

// Opens |url| according to |target| in a new tab related to |source|, then
// closes |source| when it was an empty/NTP tab. Soft-fails (no-op) when the
// browser or container cannot be resolved.
void ApplyTrafficControlTarget(content::WebContents* source,
                               const GURL& url,
                               const mojom::TargetPtr& target);

}  // namespace traffic_control

#endif  // BRAVE_BROWSER_TRAFFIC_CONTROL_TRAFFIC_CONTROL_APPLY_H_
