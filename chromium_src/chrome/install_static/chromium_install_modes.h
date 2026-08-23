/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Brand-specific types and constants for Google Chrome.

#ifndef BRAVE_CHROMIUM_SRC_CHROME_INSTALL_STATIC_CHROMIUM_INSTALL_MODES_H_
#define BRAVE_CHROMIUM_SRC_CHROME_INSTALL_STATIC_CHROMIUM_INSTALL_MODES_H_

#include <stdlib.h>

#include <array>

#include "brave/components/brave_origin/buildflags/buildflags.h"
#include "chrome/app/chrome_dll_resource.h"
#include "chrome/common/chrome_icon_resources_win.h"
#include "chrome/install_static/install_constants.h"

namespace install_static {

// Brand-specific constants and install modes for Brave.

// The brand-specific company name to be included as a component of the install
// and user data directory paths. May be empty if no such dir is to be used.
inline constexpr wchar_t kCompanyPathName[] = L"Galeob";

// The brand-specific product name to be included as a component of the install
// and user data directory paths.
#if defined(OFFICIAL_BUILD)
#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
// Galeob Browser uses "Galeob-Origin" instead of "Galeob-Browser" to allow
// side-by-side installation with Brave Browser.
inline constexpr wchar_t kProductPathName[] = L"Galeob-Origin";
#else
inline constexpr wchar_t kProductPathName[] = L"Galeob-Browser";
#endif  // BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
#else
// If you change this, then you also need to change occurrences of this string
// in mini_installer_constants.cc.
inline constexpr wchar_t kProductPathName[] = L"Galeob-Browser-Development";
#endif

// The brand-specific safe browsing client name.
inline constexpr char kSafeBrowsingName[] = "chromium";

// Note: This list of indices must be kept in sync with the brand-specific
// resource strings in chrome/installer/util/prebuild/create_string_rc.
enum InstallConstantIndex {
#if defined(OFFICIAL_BUILD)
  STABLE_INDEX,
  BETA_INDEX,
  DEV_INDEX,
  NIGHTLY_INDEX,
#else
  DEVELOPER_INDEX,
#endif
  NUM_INSTALL_MODES,
};

#if defined(OFFICIAL_BUILD)

// This is overriding the upstream value and shouldn't be undef'ed
// CHROMIUM_SRC_NOLINT
#define CHROMIUM_INDEX STABLE_INDEX

// Regarding the install switch, use the same values that are in
// chrome/installer/mini_installer/configuration.cc
#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
// Galeob Browser uses separate identifiers from Brave Browser to allow
// side-by-side installation and independent update infrastructure.
inline constexpr auto kInstallModes = std::to_array<InstallConstants>({
    // The primary install mode for stable Galeob Browser.
    {
        .size = sizeof(InstallConstants),
        .index = STABLE_INDEX,  // The first mode is for stable/beta/dev.
        .install_switch =
            "",  // No install switch for the primary install mode.
        .install_suffix =
            L"",  // Empty install suffix - "Origin" is in kProductPathName.
        .logo_suffix = L"",  // No logo suffix for the primary install mode.
        .app_guid = L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}",
        .base_app_name = L"Galeob Browser",         // A distinct base_app_name.
        .base_app_id = L"GaleobBrowser",            // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobOHTML",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Browser HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-origin",
        .pdf_prog_id_prefix = L"GaleobOPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Browser PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}",  // Active Setup GUID.
        .toast_activator_clsid = {0x8a7b6c5d,
                                  0x4e3f,
                                  0x2a1b,
                                  {0x9c, 0x8d, 0x7e, 0x6f, 0x5a, 0x4b, 0x3c,
                                   0x2d}},  // Toast activator CLSID.
        .elevator_clsid = {0x1a2b3c4d,
                           0x5e6f,
                           0x7a8b,
                           {0x9c, 0x0d, 0x1e, 0x2f, 0x3a, 0x4b, 0x5c,
                            0x6d}},  // Elevator CLSID.
        .elevator_iid = {0x2b3c4d5e,
                         0x6f7a,
                         0x8b9c,
                         {0x0d, 0x1e, 0x2f, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e}},
        .default_channel_name = L"",  // The empty string means "stable".
        .channel_strategy = ChannelStrategy::FLOATING,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_MAINFRAME,  // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012153-",  // App container sid prefix for sandbox.
    },
    // A secondary install mode for Galeob Browser Beta
    {
        .size = sizeof(InstallConstants),
        .index = BETA_INDEX,  // The mode for the side-by-side beta channel.
        .install_switch = "chrome-beta",  // Install switch.
        .install_suffix = L"-Beta",       // Install suffix.
        .logo_suffix = L"Beta",           // Logo suffix.
        .app_guid =
            L"{93B1ABC0-67FF-4928-8514-D3D91A36CB1A}",  // A distinct app GUID.
        .base_app_name = L"Galeob Browser Beta",     // A distinct base_app_name.
        .base_app_id = L"GaleobBrowserBeta",         // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobOBHTML",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Browser Beta HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-origin-beta",
        .pdf_prog_id_prefix = L"GaleobOBPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Browser Beta PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{93B1ABC0-67FF-4928-8514-D3D91A36CB1A}",  // Active Setup GUID.
        .toast_activator_clsid = {0x3c4d5e6f,
                                  0x7a8b,
                                  0x9c0d,
                                  {0x1e, 0x2f, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e,
                                   0x8f}},  // Toast activator CLSID.
        .elevator_clsid = {0x4d5e6f7a,
                           0x8b9c,
                           0x0d1e,
                           {0x2f, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f,
                            0x9a}},  // Elevator CLSID.
        .elevator_iid = {0x5e6f7a8b,
                         0x9c0d,
                         0x1e2f,
                         {0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f, 0x9a, 0x0b}},
        .default_channel_name = L"beta",  // Forced channel name.
        .channel_strategy = ChannelStrategy::FIXED,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kBetaApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_X005_BETA,      // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012154-",  // App container sid prefix for sandbox.
    },
    // A secondary install mode for Galeob Browser Dev
    {
        .size = sizeof(InstallConstants),
        .index = DEV_INDEX,  // The mode for the side-by-side dev channel.
        .install_switch = "chrome-dev",  // Install switch.
        .install_suffix = L"-Dev",       // Install suffix.
        .logo_suffix = L"Dev",           // Logo suffix.
        .app_guid =
            L"{4792BB4B-060C-4BB4-9E84-3F4DAE526146}",  // A distinct app GUID.
        .base_app_name = L"Galeob Browser Dev",      // A distinct base_app_name.
        .base_app_id = L"GaleobBrowserDev",          // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobODHTML",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Browser Dev HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-origin-dev",
        .pdf_prog_id_prefix = L"GaleobODPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Browser Dev PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{4792BB4B-060C-4BB4-9E84-3F4DAE526146}",  // Active Setup GUID.
        .toast_activator_clsid = {0x6f7a8b9c,
                                  0x0d1e,
                                  0x2f3a,
                                  {0x4b, 0x5c, 0x6d, 0x7e, 0x8f, 0x9a, 0x0b,
                                   0x1c}},  // Toast activator CLSID.
        .elevator_clsid = {0x7a8b9c0d,
                           0x1e2f,
                           0x3a4b,
                           {0x5c, 0x6d, 0x7e, 0x8f, 0x9a, 0x0b, 0x1c,
                            0x2d}},  // Elevator CLSID.
        .elevator_iid = {0x8b9c0d1e,
                         0x2f3a,
                         0x4b5c,
                         {0x6d, 0x7e, 0x8f, 0x9a, 0x0b, 0x1c, 0x2d, 0x3e}},
        .default_channel_name = L"dev",  // Forced channel name.
        .channel_strategy = ChannelStrategy::FIXED,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kDevApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_X004_DEV,      // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012155-",  // App container sid prefix for sandbox.
    },
    // A secondary install mode for Galeob Browser SxS (nightly).
    {
        .size = sizeof(InstallConstants),
        .index =
            NIGHTLY_INDEX,  // The mode for the side-by-side nightly channel.
        .install_switch = "chrome-sxs",  // Install switch.
        .install_suffix = L"-Nightly",   // Install suffix.
        .logo_suffix = L"Canary",        // Logo suffix.
        .app_guid =
            L"{0C600423-CD15-48BC-86E4-2A2E34D2C9C7}",  // A distinct app GUID.
        .base_app_name = L"Galeob Browser Nightly",  // A distinct base_app_name.
        .base_app_id = L"GaleobBrowserNightly",      // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobOSHTM",   // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Browser Nightly HTML Document",  // Browser ProgID
                                                    // description.
        .direct_launch_url_scheme = "galeob-origin-nightly",
        .pdf_prog_id_prefix = L"GaleobOSPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Browser Nightly PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{0C600423-CD15-48BC-86E4-2A2E34D2C9C7}",  // Active Setup GUID.
        .toast_activator_clsid = {0x9c0d1e2f,
                                  0x3a4b,
                                  0x5c6d,
                                  {0x7e, 0x8f, 0x9a, 0x0b, 0x1c, 0x2d, 0x3e,
                                   0x4f}},  // Toast activator CLSID.
        .elevator_clsid = {0x0d1e2f3a,
                           0x4b5c,
                           0x6d7e,
                           {0x8f, 0x9a, 0x0b, 0x1c, 0x2d, 0x3e, 0x4f,
                            0x5a}},  // Elevator CLSID.
        .elevator_iid = {0x1e2f3a4b,
                         0x5c6d,
                         0x7e8f,
                         {0x9a, 0x0b, 0x1c, 0x2d, 0x3e, 0x4f, 0x5a, 0x6b}},
        .default_channel_name = L"nightly",  // Forced channel name.
        .channel_strategy = ChannelStrategy::FIXED,
        .supports_system_level = true,  // Support system-level installs.
        .supports_set_as_default_browser =
            true,  // Support in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kSxSApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_SXS,           // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012156-",  // App container sid prefix for sandbox.
    },
});
#else   // !BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
inline constexpr auto kInstallModes = std::to_array<InstallConstants>({
    // The primary install mode for stable Brave.
    {
        .size = sizeof(InstallConstants),
        .index = STABLE_INDEX,  // The first mode is for stable/beta/dev.
        .install_switch =
            "",  // No install switch for the primary install mode.
        .install_suffix =
            L"",  // Empty install_suffix for the primary install mode.
        .logo_suffix = L"",  // No logo suffix for the primary install mode.
        .app_guid = L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}",
        .base_app_name = L"Galeob",              // A distinct base_app_name.
        .base_app_id = L"Galeob",                // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobHTML",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-browser",
        .pdf_prog_id_prefix = L"GaleobPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}",  // Active Setup GUID.
        .toast_activator_clsid = {0x6c9646d,
                                  0x2807,
                                  0x44c0,
                                  {0x97, 0xd2, 0x6d, 0xa0, 0xdb, 0x62, 0x3d,
                                   0xb4}},  // Toast activator CLSID.
        .elevator_clsid = {0x576b31af,
                           0x6369,
                           0x4b6b,
                           {0x85, 0x60, 0xe4, 0xb2, 0x3, 0xa9, 0x7a,
                            0x8b}},  // Elevator CLSID.
        .elevator_iid = {0xf396861e,
                         0x0c8e,
                         0x4c71,
                         {0x82, 0x56, 0x2f, 0xae, 0x6d, 0x75, 0x9c, 0xe9}},
        .default_channel_name = L"",  // The empty string means "stable".
        .channel_strategy = ChannelStrategy::FLOATING,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_MAINFRAME,  // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012149-",  // App container sid prefix for sandbox.
    },
    // A secondary install mode for Brave Beta
    {
        .size = sizeof(InstallConstants),
        .index = BETA_INDEX,  // The mode for the side-by-side beta channel.
        .install_switch = "chrome-beta",  // Install switch.
        .install_suffix = L"-Beta",       // Install suffix.
        .logo_suffix = L"Beta",           // Logo suffix.
        .app_guid =
            L"{ECA07209-8DF4-4A40-A3DE-2357ECD88256}",  // A distinct app GUID.
        .base_app_name = L"Galeob Beta",           // A distinct base_app_name.
        .base_app_id = L"GaleobBeta",              // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobBHTML",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Beta HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-browser-beta",
        .pdf_prog_id_prefix = L"GaleobBPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Beta PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{ECA07209-8DF4-4A40-A3DE-2357ECD88256}",  // Active Setup GUID.
        .toast_activator_clsid = {0x9560028d,
                                  0xcca,
                                  0x49f0,
                                  {0x8d, 0x47, 0xef, 0x22, 0xbb, 0xc4, 0xb,
                                   0xa7}},  // Toast activator CLSID.
        .elevator_clsid = {0x2313f1cd,
                           0x41f3,
                           0x4347,
                           {0xbe, 0xc0, 0xd7, 0x22, 0xca, 0x41, 0x2c,
                            0x75}},  // Elevator CLSID.
        .elevator_iid = {0x9ebad7ac,
                         0x6e1e,
                         0x4a1c,
                         {0xaa, 0x85, 0x1a, 0x70, 0xca, 0xda, 0x8d, 0x82}},
        .default_channel_name = L"beta",  // Forced channel name.
        .channel_strategy = ChannelStrategy::FIXED,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kBetaApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_X005_BETA,      // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012150-",  // App container sid prefix for sandbox.
    },
    // A secondary install mode for Brave Dev
    {
        .size = sizeof(InstallConstants),
        .index = DEV_INDEX,  // The mode for the side-by-side dev channel.
        .install_switch = "chrome-dev",  // Install switch.
        .install_suffix = L"-Dev",       // Install suffix.
        .logo_suffix = L"Dev",           // Logo suffix.
        .app_guid =
            L"{DE14EB69-13A1-4AB8-8EB7-647505B61958}",  // A distinct app GUID.
        .base_app_name = L"Galeob Dev",            // A distinct base_app_name.
        .base_app_id = L"GaleobDev",               // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobDHTML",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Dev HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-browser-dev",
        .pdf_prog_id_prefix = L"GaleobDPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Dev PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{DE14EB69-13A1-4AB8-8EB7-647505B61958}",  // Active Setup GUID.
        .toast_activator_clsid = {0x20b22981,
                                  0xf63a,
                                  0x47a6,
                                  {0xa5, 0x47, 0x69, 0x1c, 0xc9, 0x4c, 0xae,
                                   0xe0}},  // Toast activator CLSID.
        .elevator_clsid = {0x9129ed6a,
                           0x11d3,
                           0x43b7,
                           {0xb7, 0x18, 0x8f, 0x82, 0x61, 0x45, 0x97,
                            0xa3}},  // Elevator CLSID.
        .elevator_iid = {0x1e43c77b,
                         0x48e6,
                         0x4a4c,
                         {0x9d, 0xb2, 0xc2, 0x97, 0x17, 0x06, 0xc2, 0x55}},
        .default_channel_name = L"dev",  // Forced channel name.
        .channel_strategy = ChannelStrategy::FIXED,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kDevApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_X004_DEV,      // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012151-",  // App container sid prefix for sandbox.
    },
    // A secondary install mode for Brave SxS (canary).
    {
        .size = sizeof(InstallConstants),
        .index =
            NIGHTLY_INDEX,  // The mode for the side-by-side nightly channel.
        .install_switch = "chrome-sxs",  // Install switch.
        .install_suffix = L"-Nightly",   // Install suffix.
        .logo_suffix = L"Canary",        // Logo suffix.
        .app_guid =
            L"{D2DDDB15-F645-4391-8D19-214230EA32D1}",  // A distinct app GUID.
        .base_app_name = L"Galeob Nightly",        // A distinct base_app_name.
        .base_app_id = L"GaleobNightly",           // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobSSHTM",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Nightly HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-browser-nightly",
        .pdf_prog_id_prefix = L"GaleobSSPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Nightly PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{D2DDDB15-F645-4391-8D19-214230EA32D1}",  // Active Setup GUID.
        .toast_activator_clsid = {0xf2edbc59,
                                  0x7217,
                                  0x4da5,
                                  {0xa2, 0x59, 0x3, 0x2, 0xda, 0x6a, 0x0,
                                   0xe1}},  // Toast activator CLSID.
        .elevator_clsid = {0x1ce2f84f,
                           0x70cb,
                           0x4389,
                           {0x87, 0xdb, 0xd0, 0x99, 0x48, 0x30, 0xbb,
                            0x17}},  // Elevator CLSID.
        .elevator_iid = {0x1db2116f,
                         0x71b7,
                         0x49f0,
                         {0x89, 0x70, 0x33, 0xb1, 0xda, 0xcf, 0xb0, 0x72}},
        .default_channel_name = L"nightly",  // Forced channel name.
        .channel_strategy = ChannelStrategy::FIXED,
        .supports_system_level = true,  // Support system-level installs.
        .supports_set_as_default_browser =
            true,  // Support in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kSxSApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_SXS,           // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012152-",  // App container sid prefix for sandbox.
    },
});
#endif  // BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
#else

// CHROMIUM_SRC_NOLINT
#define CHROMIUM_INDEX DEVELOPER_INDEX

inline constexpr auto kInstallModes = std::to_array<InstallConstants>({
    // The primary (and only) install mode for Brave developer build.
    {
        .size = sizeof(InstallConstants),
        .index = DEVELOPER_INDEX,  // The one and only mode for developer mode.
        .install_switch =
            "",  // No install switch for the primary install mode.
        .install_suffix =
            L"",  // Empty install_suffix for the primary install mode.
        .logo_suffix = L"",  // No logo suffix for the primary install mode.
        .app_guid =
            L"",  // Empty app_guid since no integraion with Brave Update.
        .base_app_name = L"Galeob Development",     // A distinct base_app_name.
        .base_app_id = L"GaleobDevelopment",        // A distinct base_app_id.
        .browser_prog_id_prefix = L"GaleobDevHTM",  // Browser ProgID prefix.
        .browser_prog_id_description =
            L"Galeob Development HTML Document",  // Browser ProgID description.
        .direct_launch_url_scheme = "galeob-browser-development",
        .pdf_prog_id_prefix = L"GaleobDevPDF",  // PDF ProgID prefix.
        .pdf_prog_id_description =
            L"Galeob Development PDF Document",  // PDF ProgID description.
        .active_setup_guid =
            L"{D6527C63-5CDD-4EF3-9299-1504E17CBD18}",  // Active Setup GUID.
        .toast_activator_clsid = {0xeb41c6e8,
                                  0xba35,
                                  0x4c06,
                                  {0x96, 0xe8, 0x6f, 0x30, 0xf1, 0x8c, 0xa5,
                                   0x5c}},  // Toast activator CLSID.
        .elevator_clsid = {0x5693e62d,
                           0xd6,
                           0x4421,
                           {0xaf, 0xe8, 0x58, 0xf3, 0xc9, 0x47, 0x43,
                            0x6a}},  // Elevator CLSID.
        .elevator_iid = {0x17239bf1,
                         0xa1dc,
                         0x4642,
                         {0x84, 0x6c, 0x1b, 0xac, 0x85, 0xf9, 0x6a, 0x10}},
        .default_channel_name =
            L"",  // Empty default channel name since no update integration.
        .channel_strategy = ChannelStrategy::UNSUPPORTED,
        .supports_system_level = true,  // Supports system-level installs.
        .supports_set_as_default_browser =
            true,  // Supports in-product set as default browser UX.
        .app_icon_resource_index =
            icon_resources::kApplicationIndex,  // App icon resource index.
        .app_icon_resource_id = IDR_MAINFRAME,  // App icon resource id.
        .sandbox_sid_prefix =
            L"S-1-15-2-3251537155-1984446955-2931258699-841473695-1938553385-"
            L"934012148-",  // App container sid prefix for sandbox.
    },
});
#endif

}  // namespace install_static

#endif  // BRAVE_CHROMIUM_SRC_CHROME_INSTALL_STATIC_CHROMIUM_INSTALL_MODES_H_
