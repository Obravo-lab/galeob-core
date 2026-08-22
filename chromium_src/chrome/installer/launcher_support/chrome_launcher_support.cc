/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_origin/buildflags/buildflags.h"

namespace chrome_launcher_support {
namespace {

// Galeob Update registry settings.
const wchar_t kInstallationRegKey[] =
    L"Software\\Galeob\\Update\\ClientState";

// Copied from brave/chromium_src/chrome/install_static/chromium_install_modes.h
#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
const wchar_t kBrowserAppGuid[] = L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}";
const wchar_t kSxSBrowserAppGuid[] = L"{0C600423-CD15-48BC-86E4-2A2E34D2C9C7}";
#else
const wchar_t kBrowserAppGuid[] = L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}";
const wchar_t kSxSBrowserAppGuid[] = L"{D2DDDB15-F645-4391-8D19-214230EA32D1}";
#endif  // BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)

// Copied from util_constants.cc.
const wchar_t kChromeExe[] = L"galeob.exe";

}  // namespace
}  // namespace chrome_launcher_support

#include <chrome/installer/launcher_support/chrome_launcher_support.cc>
