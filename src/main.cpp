// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// SPDX-FileCopyrightText: 2010 ActiveState Software Inc.
// SPDX-FileCopyrightText: 2022 AppDirsCPP contributors
// SPDX-License-Identifier: MIT

#include "AppDirsCPP.hpp"
#include <internal.hpp>
#include <cstdint>
#include <string>
#include <cerrno>

static inline void splitMultiPath(
    _CXTSTR multipath,
    std::vector<_CXTSTR>& full_paths)
{
	size_t pos = 0;
	size_t counter = 0;
	while ((pos = multipath.find(pathsep_cstr, pos)) != _CXTSTR::npos) {
		counter++;
		full_paths.push_back(multipath.substr(0, pos));
		multipath.erase(0, pos + pathsep_cstr.length());
	}
	if (counter == 0) {
		full_paths.push_back(multipath);
	}
}


#if defined(_WIN32)
#include <Shlobj.h>

static inline void wins_getFolderPath(
    const int csidl,
    const KNOWNFOLDERID rfid,
    _CXTSTR& full_path)
{
	// Windows Vista or later
	if (IsWindowsVistaOrGreater()) {
		LPWSTR path = NULL;
		HRESULT result = SHGetKnownFolderPath(rfid, KF_FLAG_DEFAULT, NULL, &path);
		if (SUCCEEDED(result)) {
			full_path = path;
			CoTaskMemFree(path);
		}
	}
	// Windows XP or earlier
	else {
		wchar_t path[MAX_PATH]{};
		SHGetFolderPathW(NULL, csidl, NULL, 0, path);
		if (path[0] != L'\0') {
			full_path = path;
		}
	}
}

#else
#include <pwd.h>
#include <unistd.h>
static _CXTSTR getUserDirectory()
{
	const char* path = getenv("HOME");
	if (path) {
		return path;
	}
	const passwd* pw = getpwuid(getuid());

	if (pw) {
		return pw->pw_dir;
	}

	return "~";
}
#endif

static _CXTSTR append_path(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version)
{
	_CXTSTR append_path_str;
#if defined(_WIN32) // Only for Windows
	if (appauthor) {
		append_path_str.append(slash_cat + *appauthor);
	}
#endif

	if (appname) {
		append_path_str.append(slash_cat + *appname);
		if (version) {
			append_path_str.append(slash_cat + *version);
		}
	}
	return append_path_str;
}

static _CXTSTR append_path_cache(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    bool opinion)
{
	_CXTSTR append_path_str;
#if defined(_WIN32) // Only for Windows
	if (appauthor) {
		append_path_str.append(slash_cat + *appauthor);
	}
#endif

	if (appname) {
		append_path_str.append(slash_cat + *appname);

#if defined(_WIN32) // Only for Windows
		if (opinion) {
			append_path_str.append(slash_cat cache_str);
		}
#endif

		if (version) {
			append_path_str.append(slash_cat + *version);
		}
	}
	return append_path_str;
}

_CXTSTR user_data_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool roaming,
    int* error)
{
	_CXTSTR full_path;

#if defined(_WIN32)
	const int csidl = roaming ? CSIDL_APPDATA : CSIDL_LOCAL_APPDATA;
	const KNOWNFOLDERID rfid = roaming ? FOLDERID_RoamingAppData : FOLDERID_LocalAppData;
	wins_getFolderPath(csidl, rfid, full_path);
#elif defined(__APPLE__)
	full_path = getUserDirectory() + "/Library/Application Support";
#else
	const char* path = getenv("XDG_DATA_HOME");
	if (path) {
		full_path = path;
	}
	else {
		full_path = getUserDirectory() + "/.local/share";
	}
#endif

	if (full_path.empty()) {
		*error = errno;
		return full_path;
	}

	const _CXTSTR& append_path_str = append_path(appname, appauthor, version);
	if (!append_path_str.empty()) {
		full_path.append(append_path_str);
	}

	*error = 0;
	return full_path;
}

std::vector<_CXTSTR> site_data_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool multipath,
    int* error)
{
	std::vector<_CXTSTR> full_paths;

#if defined(_WIN32)
	_CXTSTR path;
	wins_getFolderPath(CSIDL_COMMON_APPDATA, FOLDERID_ProgramData, path);
	if (!path.empty()) {
		full_paths.push_back(path);
	}
#elif defined(__APPLE__)
	full_paths.push_back("/Library/Application Support");
#else
	const char* paths = getenv("XDG_DATA_DIRS");
	if (paths) {
		splitMultiPath(paths, full_paths);
	}
	else {
		full_paths.push_back("/usr/local/share");
		full_paths.push_back("/usr/share");
	}

	if (full_paths.empty()) {
		*error = errno;
		return full_paths;
	}

	if (!multipath) {
		full_paths.resize(1);
	}
#endif

	if (full_paths.empty()) {
		*error = errno;
		return full_paths;
	}

	_CXTSTR append_path_str = append_path(appname, appauthor, version);
	if (!append_path_str.empty()) {
		for (auto& full_path_i : full_paths) {
			full_path_i.append(append_path_str);
		}
	}

	*error = 0;
	return full_paths;
}

_CXTSTR user_config_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool roaming,
    int* error)
{
#if defined(_WIN32)
	// same as user_data_dir
	return user_data_dir(appname, appauthor, version, roaming, error);
#elif defined(__APPLE__)
	_CXTSTR full_path = getUserDirectory() + "/Library/Preferences";
#else
	_CXTSTR full_path;

	const char* path = getenv("XDG_CONFIG_HOME");
	if (path) {
		full_path = path;
	}
	else {
		full_path = getUserDirectory() + "/.config";
	}
#endif
#if !defined(_WIN32)
	if (full_path.empty()) {
		*error = errno;
		return full_path;
	}

	const _CXTSTR& append_path_str = append_path(appname, nullptr, version);
	if (!append_path_str.empty()) {
		full_path.append(append_path_str);
	}

	*error = 0;
	return full_path;
#endif
}

std::vector<_CXTSTR> site_config_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool multipath,
    int* error)
{
#if defined(_WIN32)
	// same as site_data_dir
	return site_data_dir(appname, appauthor, version, multipath, error);
#elif defined(__APPLE__)
	std::vector<_CXTSTR> full_paths;
	full_paths.push_back("/Library/Preferences");

	const _CXTSTR& append_path_str = append_path(appname, nullptr, nullptr);
	if (!append_path_str.empty()) {
		for (auto& full_path_i : full_paths) {
			full_path_i.append(append_path_str);
		}
	}
	return full_paths;
#else
	std::vector<_CXTSTR> full_paths;

	const char* paths = getenv("XDG_CONFIG_DIRS");
	if (paths) {
		splitMultiPath(paths, full_paths);
	}
	else {
		full_paths.push_back("/etc/xdg");
	}

	if (full_paths.empty()) {
		*error = errno;
		return full_paths;
	}

	if (!multipath) {
		full_paths.resize(1);
	}

	const _CXTSTR& append_path_str = append_path(appname, nullptr, version);
	if (!append_path_str.empty()) {
		for (auto& full_path_i : full_paths) {
			full_path_i.append(append_path_str);
		}
	}

	*error = 0;
	return full_paths;
#endif
}

_CXTSTR user_cache_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool opinion,
    int* error)
{
	_CXTSTR full_path;

#if defined(_WIN32)
	wins_getFolderPath(CSIDL_LOCAL_APPDATA, FOLDERID_LocalAppData, full_path);
#elif defined(__APPLE__)
	full_path = getUserDirectory() + "/Library/Caches";
#else
	const char* path = getenv("XDG_CACHE_HOME");
	if (path) {
		full_path = path;
	}
	else {
		full_path = getUserDirectory() + "/.cache";
	}
#endif

	if (full_path.empty()) {
		*error = errno;
		return full_path;
	}

	const _CXTSTR& append_path_str = append_path_cache(appname, appauthor, version, opinion);
	if (!append_path_str.empty()) {
		full_path.append(append_path_str);
	}

	*error = 0;
	return full_path;
}

_CXTSTR user_state_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool roaming,
    int* error)
{
#if defined(_WIN32) || defined(__APPLE__)
	// same as user_data_dir
	return user_data_dir(appname, appauthor, version, roaming, error);
#else
	_CXTSTR full_path;

	const char* path = getenv("XDG_STATE_HOME");
	if (path) {
		full_path = path;
	}
	else {
		full_path = getUserDirectory() + "/.local/state";
	}

	if (full_path.empty()) {
		*error = errno;
		return full_path;
	}

	const _CXTSTR& append_path_str = append_path(appname, nullptr, version);
	if (!append_path_str.empty()) {
		full_path.append(append_path_str);
	}

	*error = 0;
	return full_path;
#endif
}

_CXTSTR user_log_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool opinion,
    int* error)
{
	int error_local;
	_CXTSTR full_path;
#if defined(_WIN32)
	full_path = user_data_dir(appname, appauthor, version, false, &error_local);
#elif !defined(__APPLE__)
	full_path = user_cache_dir(appname, appauthor, version, true, &error_local);
#else
	full_path = getUserDirectory() + "/Library/Logs";

	const _CXTSTR& append_path_str = append_path(appname, appauthor, version);
	if (!append_path_str.empty()) {
		full_path.append(append_path_str);
	}
	if (error_local) {
		*error = error_local;
		return full_path;
	}
#endif

#if !defined(__APPLE__)
	if (opinion) {
		full_path.append(slash_cat log_str);
	}
#endif

	*error = error_local;
	return full_path;
}
