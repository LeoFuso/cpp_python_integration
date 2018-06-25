cmake_minimum_required(VERSION 2.8)
project(POC_C_PYTHON_INTEGRATION)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 11)

find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(Total SHARED total.c)

target_link_libraries(Total ${PYTHON_LIBRARIES})

# Tweaks the name of the library to match what Python expects
set_target_properties(Total PROPERTIES SUFFIX .so)
set_target_properties(Total PROPERTIES PREFIX "")

# Copy the Python's main file to the library directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/main.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})