// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// SPDX-FileCopyrightText: 2010 ActiveState Software Inc.
// SPDX-FileCopyrightText: 2022 AppDirsCPP contributors
// SPDX-License-Identifier: MIT

#if defined(_WIN32)
#define _CXT(x) L##x
#define pathsep L";"
#else
#define _CXT(x) x
#define pathsep ":"
#endif

#define cache_str _CXT("Cache")
#if defined(_WIN32) || defined(__APPLE)
#define log_str _CXT("Logs")
#else
#define log_str _CXT("log")
#endif

#if defined(_WIN32)
#define slash_cat L"\\"
#define cache_cat L"\\\\" cache_str
#define log_cat L"\\\\" log_str
#elif defined(__APPLE__)
#else
#endif

#if !defined(_WIN32)
#define slash_cat "/"
#define AppDirsCPP_cat "/" AppDirsCPP_str
#define AppAuthor_cat "/" AppAuthor_str
#define version_cat "/" version_str
#endif
