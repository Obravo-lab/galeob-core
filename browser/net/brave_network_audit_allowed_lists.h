/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_NET_BRAVE_NETWORK_AUDIT_ALLOWED_LISTS_H_
#define BRAVE_BROWSER_NET_BRAVE_NETWORK_AUDIT_ALLOWED_LISTS_H_

#include <array>
#include <string_view>

#include "base/containers/fixed_flat_set.h"

namespace brave {

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlProtocols =
    base::MakeFixedFlatSet<std::string_view>({
        "chrome-extension",
        "chrome",
        "brave",
        "file",
        "data",
        "blob",
    });

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlPrefixes = std::to_array<std::string_view>({
    // allowed because it 307's to https://componentupdater.galeob.fr
    "https://componentupdater.galeob.fr/service/update2",
    "https://crxdownload.galeob.fr/crx/blobs/",

    // Omaha/Sparkle
    "https://updates.galeob.fr/",

    // stats/referrals
    "https://usage-ping.galeob.fr/",

    // needed for DoH on Mac build machines
    "https://dns.google/dns-query",

    // needed for DoH on Mac build machines
    "https://chrome.cloudflare-dns.com/dns-query",

    // for fetching tor client updater component
    "https://tor.galeob.fr/",

    // brave sync v2 production
    "https://sync-v2.galeob.fr/v2",

    // brave sync v2 staging
    "https://sync-v2-staging.galeob.fr/v2",

    // brave sync v2 dev
    "https://sync-v2-dev.galeob.fr/v2",

    // brave A/B testing
    "https://variations.galeob.fr/seed",

    // Brave News (production)
    "https://brave-today-cdn.galeob.fr/",

    // Brave's Privacy-focused CDN
    "https://pcdn.galeob.fr/",

    // p3a
    "https://star-randsrv.galeob.fr/",

    // Other
    "https://brave-core-ext.galeob.fr/",
    "https://dict.galeob.fr/",
    "https://go-updater.galeob.fr/",
    "https://redirector.galeob.fr/",
    "https://safebrowsing.galeob.fr/",
    "https://static.galeob.fr/",
    "https://static1.galeob.fr/",
});

}  // namespace brave

#endif  // BRAVE_BROWSER_NET_BRAVE_NETWORK_AUDIT_ALLOWED_LISTS_H_
