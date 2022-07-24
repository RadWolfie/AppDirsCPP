# CMakeList.txt : CMake solution for appdirsC.
#
cmake_minimum_required (VERSION 3.10.2)

project (AppDirsCPP)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
 set(AppDirsCPP_DEFAULT_CONFIGS ON)
 enable_testing()
else()
 set(AppDirsCPP_DEFAULT_CONFIGS OFF)
endif()

option(AppDirsCPP_INSTALL_LIB "Install libAppDirsCPP library" ${AppDirsCPP_DEFAULT_CONFIGS})

option(AppDirsCPP_BUILD_UNIT_TEST "Build AppDirsCPP's Unit Test" ${AppDirsCPP_DEFAULT_CONFIGS})

# For any optional tools, use list(APPEND AppDirsCPP_INSTALL_TOOLS "tool_name")

if(AppDirsCPP_INSTALL_LIB)
 list(APPEND AppDirsCPP_INSTALL_TOOLS "libAppDirsCPP")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory("${PROJECT_SOURCE_DIR}/projects")

if (AppDirsCPP_INSTALL_TOOLS)
 if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  install(FILES "LICENSE" "README.md" DESTINATION .)
 else()
  install(FILES "LICENSE" "README.md" DESTINATION "AppDirsCPP")
 endif()
endif()
