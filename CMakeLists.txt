cmake_minimum_required(VERSION 2.8)

PROJECT(Koala)
include("internal.cmake")
set_default_compiler_linker_config()

# Tell CMake to create the executable

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
    )
add_executable(Koala ${source})

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/core)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/effects)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/config)
set_target_properties(Koala PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")
