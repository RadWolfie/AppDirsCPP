# CMakeList.txt : CMake project for libAppDirsCPP.
#
cmake_minimum_required (VERSION 3.10.2)

project (libAppDirsCPP LANGUAGES CXX)

file(GLOB INCLUDES
 "${AppDirsCPP_SOURCE_DIR}/include/AppDirsCPP.hpp"
 "${AppDirsCPP_SOURCE_DIR}/tests/internal.h"
 "${AppDirsCPP_SOURCE_DIR}/tests/internal.hpp"
 "${AppDirsCPP_SOURCE_DIR}/LICENSE"
)
source_group(TREE ${AppDirsCPP_SOURCE_DIR} FILES ${INCLUDES})

file(GLOB_RECURSE SOURCES
 "${AppDirsCPP_SOURCE_DIR}/src/main.cpp"
)
source_group(TREE ${AppDirsCPP_SOURCE_DIR} FILES ${SOURCES})

add_library (${PROJECT_NAME} ${INCLUDES} ${SOURCES})

# NOTES:
# Using INTERFACE keyword will not work within the project. Only PUBLIC/PRIVATE keywords does.
target_include_directories(${PROJECT_NAME}
 PUBLIC "${AppDirsCPP_SOURCE_DIR}/include"
 PRIVATE "${AppDirsCPP_SOURCE_DIR}/tests"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)

set_target_properties(${PROJECT_NAME} PROPERTIES
 PUBLIC_HEADER "${INCLUDES}"
 CXX_STANDARD 11
 CXX_STANDARD_REQUIRED ON
 FOLDER AppDirsCPP
)

if(AppDirsCPP_INSTALL_LIB)
 install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include
  LIBRARY DESTINATION lib_shared
  ARCHIVE DESTINATION lib_static
 )
endif()
