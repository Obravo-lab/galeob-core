/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/installer/util/google_update_constants.h"

#include "brave/components/brave_origin/buildflags/buildflags.h"

#define kChromeUpgradeCode kChromeUpgradeCode_Unused
#define kGoogleUpdateUpgradeCode kGoogleUpdateUpgradeCode_Unused
#define kGoogleUpdateSetupExe kGoogleUpdateSetupExe_Unused
#define kRegPathClients kRegPathClients_Unused
#define kRegPathClientState kRegPathClientState_Unused
#define kRegPathClientStateMedium kRegPathClientStateMedium_Unused
#define kRegPathGoogleUpdate kRegPathGoogleUpdate_Unused

#include <chrome/installer/util/google_update_constants.cc>

#undef kChromeUpgradeCode
#undef kGoogleUpdateUpgradeCode
#undef kGoogleUpdateSetupExe
#undef kRegPathClients
#undef kRegPathClientState
#undef kRegPathClientStateMedium
#undef kRegPathGoogleUpdate

namespace google_update {

// kChromeUpgradeCode is browser-specific to allow side-by-side installation.
#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
const wchar_t kChromeUpgradeCode[] = L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}";
#else
const wchar_t kChromeUpgradeCode[] = L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}";
#endif

// Updater constants are shared between Galeob builds since
// they use the same updater infrastructure.
const wchar_t kGoogleUpdateUpgradeCode[] =
    L"{B131C935-9BE6-41DA-9599-1F776BEB8019}";
const wchar_t kGoogleUpdateSetupExe[] = L"GaleobUpdateSetup.exe";
const wchar_t kRegPathClients[] = L"Software\\Galeob\\Update\\Clients";
const wchar_t kRegPathClientState[] =
    L"Software\\Galeob\\Update\\ClientState";
const wchar_t kRegPathClientStateMedium[] =
    L"Software\\Galeob\\Update\\ClientStateMedium";
const wchar_t kRegPathGoogleUpdate[] = L"Software\\Galeob\\Update";

}  // namespace google_update
