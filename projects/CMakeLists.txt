# CMakeList.txt : generate all projects
#
cmake_minimum_required (VERSION 3.10.2)

add_subdirectory("libAppDirsCPP")

if(AppDirsCPP_BUILD_UNIT_TEST)
 add_subdirectory("tests")
endif()
