cmake_minimum_required(VERSION 2.8)

PROJECT(Koala)
include("internal.cmake")
set_default_compiler_linker_config()

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/layout)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/event)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/widget)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/texture)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/core)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/effects)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/config)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/lazy)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
# Tell CMake to create the executable

file(GLOB LAYOUT_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/*.cpp
    )

file(GLOB EVENT_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/event/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/event/*.cpp
    )

file(GLOB TEXTURE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/texture/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/texture/*.cpp
    )

file(GLOB WIDGET_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/widget/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widget/*.cpp
    )

file(GLOB SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

source_group(layout FILES ${LAYOUT_SRCS})
source_group(texture FILES ${TEXTURE_SRCS})
source_group(widget FILES ${WIDGET_SRCS})
source_group(event FILES ${EVENT_SRCS})

add_library(Koala STATIC 
	${LAYOUT_SRCS}
	${EVENT_SRCS} 
	${TEXTURE_SRCS}
	${WIDGET_SRCS}
	${SRCS}
	)

set(SKIA_LIBS skia_animator.lib skia_core.lib skia_effects.lib skia_images.lib skia_opts.lib skia_opts_ssse3.lib skia_pdf.lib skia_ports.lib
	skia_sfnt.lib skia_skgpu.lib skia_utils.lib skia_xml.lib skia_xps.lib)
target_link_libraries(Koala ${SKIA_LIBS} Usp10.lib opengl32.lib)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gtest)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gtest/include)
set(unittest_source unittest/layout_unittest.cpp thirdparty/gtest/src/gtest-all.cc unittest/gtest_main.cpp)
add_executable(KoalaUnittest ${unittest_source})
target_link_libraries(KoalaUnittest Koala)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
set(demo_source demo/koala_demo.cpp)
add_executable(KoalaDemo ${demo_source})
target_link_libraries(KoalaDemo Koala)

set_target_properties(KoalaDemo PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")