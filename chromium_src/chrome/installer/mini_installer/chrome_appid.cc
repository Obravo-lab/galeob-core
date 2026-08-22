/* Copyright (c) 2018 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_origin/buildflags/buildflags.h"
#include "chrome/installer/mini_installer/appid.h"

namespace google_update {

#if defined(OFFICIAL_BUILD)
#if BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
// Brave Origin uses separate app GUIDs from Brave Browser to allow
// side-by-side installation and independent update infrastructure.
const wchar_t kAppGuid[] = L"{88E1CF75-B65C-45BE-9725-BE6561ECDD51}";
const wchar_t kBetaAppGuid[] = L"{93B1ABC0-67FF-4928-8514-D3D91A36CB1A}";
const wchar_t kDevAppGuid[] = L"{4792BB4B-060C-4BB4-9E84-3F4DAE526146}";
const wchar_t kSxSAppGuid[] = L"{0C600423-CD15-48BC-86E4-2A2E34D2C9C7}";
#else
const wchar_t kAppGuid[] = L"{A343DC93-4479-4D8C-A29C-3CDE262E7334}";
const wchar_t kBetaAppGuid[] = L"{ECA07209-8DF4-4A40-A3DE-2357ECD88256}";
const wchar_t kDevAppGuid[] = L"{DE14EB69-13A1-4AB8-8EB7-647505B61958}";
const wchar_t kSxSAppGuid[] = L"{D2DDDB15-F645-4391-8D19-214230EA32D1}";
#endif  // BUILDFLAG(IS_BRAVE_ORIGIN_BRANDED)
#else
const wchar_t kAppGuid[] = L"";
#endif

}  // namespace google_update
