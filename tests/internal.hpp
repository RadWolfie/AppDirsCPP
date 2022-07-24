// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// SPDX-FileCopyrightText: 2010 ActiveState Software Inc.
// SPDX-FileCopyrightText: 2022 AppDirsCPP contributors
// SPDX-License-Identifier: MIT

#include "internal.h"

static const _CXTSTR pathsep_cstr = pathsep;

#define AppDirsCPP_str _CXT("AppDirsCPP")
#define AppAuthor_str _CXT("AppAuthor")
#define version_str _CXT("major.minor")

static const _CXTSTR AppDirsCPP_cstr = AppDirsCPP_str;
static const _CXTSTR AppAuthor_cstr = AppAuthor_str;
static const _CXTSTR version_cstr = version_str;

#if !defined(_WIN32)
#define regex std::regex
#define cout std::cout
#define AppDirsCPP_cat "/" AppDirsCPP_str
#define AppAuthor_cat "/" AppAuthor_str
#define version_cat "/" version_str
#endif

#define regex_icase std::regex_constants::icase

#if defined(_WIN32)
// Used in library + unit tests.
#include <Windows.h>
// Port VersionHelpers.h to work with later Visual Studio's incomplete includes.
static inline bool IsWindowsVistaOrGreater()
{
	OSVERSIONINFOEXW osvi{};
	DWORDLONG dwlConditionMask = 0;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	osvi.dwMajorVersion = HIBYTE(_WIN32_WINNT_VISTA);
	osvi.dwMinorVersion = LOBYTE(_WIN32_WINNT_VISTA);
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);

	return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask);
}

#define regex std::wregex
#define cout std::wcout

#define AppDirsCPP_cat L"\\\\" AppDirsCPP_str
#define AppAuthor_cat L"\\\\" AppAuthor_str
#define version_cat L"\\\\" version_str

#define cache_cat L"\\\\" cache_str
#define log_cat L"\\\\" log_str

// [^\\\\]+ == match everything except for backslash
#define user_data_regex_not_roaming_xp_earlier L"[a-z]\\:\\\\Documents and Settings\\\\[^\\\\]+\\\\Local Settings\\\\Application Data"
#define user_data_regex_roaming_xp_earlier L"[a-z]\\:\\\\Documents and Settings\\\\[^\\\\]+\\\\Application Data"
#define user_data_regex_not_roaming_vista_plus L"[a-z]\\:\\\\Users\\\\[^\\\\]+\\\\AppData\\\\Local"
#define user_data_regex_roaming_vista_plus L"[a-z]\\:\\\\Users\\\\[^\\\\]+\\\\AppData\\\\Roaming"

#define site_data_regex_xp_earlier L"[a-z]\\:\\\\Documents and Settings\\\\All Users\\\\Application Data"
#define site_data_regex_vista_later L"[a-z]\\:\\\\ProgramData"

#define site_config_regex_xp_earlier site_data_regex_xp_earlier
#define site_config_regex_vista_later site_data_regex_vista_later

#elif defined(__APPLE__)
#define user_data_regex "(~|/Users/[^/]+)/Library/Application Support"
#define site_data_regex "/Library/Application Support"
#define user_config_regex "(~|/Users/[^/]+)/Library/Preferences"
#define site_config_regex "/Library/Preferences"
#define user_cache_regex "(~|/Users/[^/]+)/Library/Caches"
#define user_state_regex user_data_regex
#define user_log_regex "(~|/Users/[^/]+)/Library/Logs"

#else
#define log_cat "/" log_str

#define user_data_regex "(~|/home/[^/]+)/\\.local/share"  // or $XDG_DATA_HOME
#define site_data_regex "(/usr/local/share|/usr/share)"   // or $XDG_DATA_DIRS[i]
#define user_config_regex "(~|/home/[^/]+)/\\.config"     // or $XDG_CONFIG_HOME
#define site_config_regex "/etc/xdg"                      // or $XDG_CONFIG_DIRS[i]
#define user_cache_regex "(~|/home/[^/]+)/\\.cache"       // or $XDG_CACHE_HOME
#define user_state_regex "(~|/home/[^/]+)/\\.local/state" // or $XDG_STATE_HOME
#define user_log_regex "(~|/home/[^/]+)/\\.cache"         // or $XDG_CACHE_HOME

#endif

#include <bitset>

template<std::size_t N>
static inline std::bitset<N> reverse_bits(const std::bitset<N> b)
{
	std::bitset<N> o;
	for (std::size_t i = 0; i < N / 2; ++i) {
		bool t = b[i];
		o[i] = b[N - i - 1];
		o[N - i - 1] = t;
	}
	return o;
}
