/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_origin/buildflags/buildflags.h"

namespace gcapi_internals {

#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
const wchar_t kChromeRegClientsKey[] =
    L"Software\\Galeob\\Update\\Clients\\"
    L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}";
const wchar_t kChromeRegClientStateKey[] =
    L"Software\\Galeob\\Update\\ClientState\\"
    L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}";
#else
const wchar_t kChromeRegClientsKey[] =
    L"Software\\Galeob\\Update\\Clients\\"
    L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}";
const wchar_t kChromeRegClientStateKey[] =
    L"Software\\Galeob\\Update\\ClientState\\"
    L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}";
#endif  // BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)

}  // namespace gcapi_internals

#include <chrome/installer/gcapi/google_update_util.cc>
