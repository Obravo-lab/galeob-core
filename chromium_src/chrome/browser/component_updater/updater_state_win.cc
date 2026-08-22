/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_origin/buildflags/buildflags.h"

namespace component_updater {
namespace {

// Galeob Update group policy settings.
const wchar_t kGoogleUpdatePoliciesKey[] =
    L"SOFTWARE\\Policies\\Galeob\\Update";
const wchar_t kCheckPeriodOverrideMinutes[] = L"AutoUpdateCheckPeriodMinutes";
const wchar_t kUpdatePolicyValue[] = L"UpdateDefault";
#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
const wchar_t kChromeUpdatePolicyOverride[] =
    L"Update{88E1CF75-B65C-45BE-9725-BE6561ECDD51}";
#else
const wchar_t kChromeUpdatePolicyOverride[] =
    L"Update{A343DC93-4479-4D8C-A29C-3CDE262E7334}";
#endif  // BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)

// Don't allow update periods longer than six weeks (Chrome release cadence).
const int kCheckPeriodOverrideMinutesMax = 60 * 24 * 7 * 6;

// Galeob Update registry settings.
const wchar_t kRegPathGoogleUpdate[] = L"Software\\Galeob\\Update";
const wchar_t kRegPathClientsGoogleUpdate[] =
    L"Software\\Galeob\\Update\\Clients\\"
    L"{B131C935-9BE6-41DA-9599-1F776BEB8019}";

}  // namespace
}  // namespace component_updater

#include <chrome/browser/component_updater/updater_state_win.cc>
