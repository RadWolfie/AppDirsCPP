# CMakeList.txt : CMake projects for libAppDirsCPP's Unit Tests.
#
cmake_minimum_required (VERSION 3.10.2)

enable_testing()
list(APPEND unit_test_projects "user_data_dir")
list(APPEND unit_test_projects "site_data_dir")
list(APPEND unit_test_projects "user_config_dir")
list(APPEND unit_test_projects "site_config_dir")
list(APPEND unit_test_projects "user_cache_dir")
list(APPEND unit_test_projects "user_state_dir")
list(APPEND unit_test_projects "user_log_dir")

file(GLOB INCLUDES
 "${AppDirsCPP_SOURCE_DIR}/include/AppDirsCPP.hpp"
 "${AppDirsCPP_SOURCE_DIR}/LICENSE"
 "${AppDirsCPP_SOURCE_DIR}/tests/internal.h"
 "${AppDirsCPP_SOURCE_DIR}/tests/internal.hpp"
)
source_group(TREE ${AppDirsCPP_SOURCE_DIR} FILES ${INCLUDES})

foreach(UnitTestProject IN LISTS unit_test_projects)
  project(${UnitTestProject} LANGUAGES CXX)
  add_executable(${UnitTestProject} ${INCLUDES} ${AppDirsCPP_SOURCE_DIR}/tests/${UnitTestProject}.cpp)

  target_compile_definitions(${UnitTestProject} PRIVATE _CRT_SECURE_NO_WARNINGS)

  target_link_libraries(${UnitTestProject} libAppDirsCPP)

  set_target_properties(${UnitTestProject} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    FOLDER AppDirsCPP/UnitTests
  )
  # NOTE: CMAKE_CROSSCOMPILING_EMULATOR is require if not using current platform system.
  add_test(NAME ${UnitTestProject} COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:${UnitTestProject}>)
endforeach()
