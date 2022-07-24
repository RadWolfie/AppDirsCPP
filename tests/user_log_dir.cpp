// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// SPDX-FileCopyrightText: 2010 ActiveState Software Inc.
// SPDX-FileCopyrightText: 2022 AppDirsC contributors
// SPDX-License-Identifier: MIT

#include <AppDirsCPP.hpp>
#include <array>
#include <cmath>
#include <regex>
#include <iostream>
#include <iomanip>

#include "internal.hpp"

#ifdef _WIN32
#define user_log_regex_xp_earlier user_data_regex_not_roaming_xp_earlier
#define user_log_regex_vista_plus user_data_regex_not_roaming_vista_plus
// XP and earlier
const std::array<const regex, 16> test_regex_xp_earlier = {
	// exclude opinion
	regex(user_log_regex_xp_earlier, regex_icase),
	regex(user_log_regex_xp_earlier AppDirsCPP_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat AppDirsCPP_cat, regex_icase),
	regex(user_log_regex_xp_earlier, regex_icase),
	regex(user_log_regex_xp_earlier AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat AppDirsCPP_cat version_cat, regex_icase),
	// include opinion
	regex(user_log_regex_xp_earlier log_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppDirsCPP_cat cache_cat log_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat log_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat AppDirsCPP_cat cache_cat log_cat, regex_icase),
	regex(user_log_regex_xp_earlier log_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppDirsCPP_cat cache_cat version_cat log_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat log_cat, regex_icase),
	regex(user_log_regex_xp_earlier AppAuthor_cat AppDirsCPP_cat cache_cat version_cat log_cat, regex_icase),
};

// Vista and later
const std::array<const regex, 16> test_regex_vista_plus = {
	// exclude opinion
	regex(user_log_regex_vista_plus, regex_icase),
	regex(user_log_regex_vista_plus AppDirsCPP_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat AppDirsCPP_cat, regex_icase),
	regex(user_log_regex_vista_plus, regex_icase),
	regex(user_log_regex_vista_plus AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat AppDirsCPP_cat version_cat, regex_icase),
	// include opinion
	regex(user_log_regex_vista_plus log_cat, regex_icase),
	regex(user_log_regex_vista_plus AppDirsCPP_cat log_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat log_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat AppDirsCPP_cat log_cat, regex_icase),
	regex(user_log_regex_vista_plus log_cat, regex_icase),
	regex(user_log_regex_vista_plus AppDirsCPP_cat version_cat log_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat log_cat, regex_icase),
	regex(user_log_regex_vista_plus AppAuthor_cat AppDirsCPP_cat version_cat log_cat, regex_icase),
};

#elif defined(__APPLE__)
const std::array<const regex, 16> test_regex_generic = {
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat, regex_icase),
};

#else
const std::array<const regex, 16> test_regex_generic = {
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat, regex_icase),
	regex(user_log_regex log_cat, regex_icase),
	regex(user_log_regex AppDirsCPP_cat log_cat, regex_icase),
	regex(user_log_regex log_cat, regex_icase),
	regex(user_log_regex AppDirsCPP_cat log_cat, regex_icase),
	regex(user_log_regex log_cat, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat log_cat, regex_icase),
	regex(user_log_regex log_cat, regex_icase),
	regex(user_log_regex AppDirsCPP_cat version_cat log_cat, regex_icase),
};

#endif

int main(int argc, char const* argv[])
{
	int error_count = 0;
	unsigned i = 0;
	std::bitset<4> param_test = i;
	const auto param_combo_total = static_cast<unsigned>(std::pow(2, param_test.size()));
	const std::array<const regex, 16>* test_regex;

#if defined(_WIN32)
	if (IsWindowsVistaOrGreater()) {
		test_regex = &test_regex_vista_plus;
	}
	else {
		test_regex = &test_regex_xp_earlier;
	}
#else
	test_regex = &test_regex_generic;
#endif

	while (i < param_combo_total) {
		int error = 0;

		const _CXTSTR* appname = param_test[0] ? &AppDirsCPP_cstr : NULL;
		const _CXTSTR* appauthor = param_test[1] ? &AppAuthor_cstr : NULL;
		const _CXTSTR* version = param_test[2] ? &version_cstr : NULL;
		bool opinion = param_test[3] ? true : false;
		const _CXTSTR& full_path = user_log_dir(appname, appauthor, version, opinion, &error);
		if (error || full_path.empty()) {
			cout << "ERROR";
		}
		else {
			cout << "INFO ";
		}
		cout << ": user_log_dir[" << std::setw(2) << i << "]:\n";
		if (!full_path.empty() && !error) {
			if (std::regex_match(full_path, (*test_regex)[i])) {
				cout << "PASS! ";
			}
			else {
				cout << "FAIL! ";
				error_count++;
			}
			cout << "params[" << reverse_bits(param_test) << "]; full_path = " << full_path << ";\n";
		}
		else {
			cout << "params[" << reverse_bits(param_test) << "]; return " << error << "!\n";
			error_count++;
		}

		param_test = ++i;
	}
	return error_count;
}
