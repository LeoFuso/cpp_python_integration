cmake_minimum_required(VERSION 2.8)
project(POC_C_PYTHON_INTEGRATION)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 11)

set(CFLAGS_O0 "-O0")
set(CFLAGS_SSE2 "-O3 -march=native")

# Set the Python version to 2.7
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(total SHARED total.c)

set_property(TARGET total PROPERTY COMPILE_FLAGS ${CFLAGS_O0})

target_link_libraries(total ${PYTHON_LIBRARIES})

# Tweaks the name of the library to match what Python expects
set_target_properties(total PROPERTIES SUFFIX .so)
set_target_properties(total PROPERTIES PREFIX "")
