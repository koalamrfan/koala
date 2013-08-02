cmake_minimum_required(VERSION 2.8)

PROJECT(layout)
include("internal.cmake")
set_default_compiler_linker_config()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the executable

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
    )
add_executable(layout ${source})

# Use the Widgets module from Qt 5.
qt5_use_modules(layout Widgets)
