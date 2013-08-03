cmake_minimum_required(VERSION 2.8)

PROJECT(Koala)
include("internal.cmake")
set_default_compiler_linker_config()

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/core)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/effects)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/config)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
# Tell CMake to create the executable

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
    )
add_executable(Koala ${source})

set_target_properties(Koala PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")

set(SKIA_LIBS skia_animator.lib skia_core.lib skia_effects.lib skia_images.lib skia_opts.lib skia_opts_ssse3.lib skia_pdf.lib skia_ports.lib
	skia_sfnt.lib skia_skgpu.lib skia_utils.lib skia_views.lib skia_xml.lib skia_xps.lib)
target_link_libraries(Koala ${SKIA_LIBS} Usp10.lib opengl32.lib)
