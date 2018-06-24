cmake_minimum_required(VERSION 2.8)

project(CPP_PYTHON_INTEGRATION)

# For development, only
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 11)

set(CXXFLAGS_O0 "-O0")
set(CXXFLAGS_SSE2 "-O3 -march=native")

# Set the Python version to default in the OS
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Build the library responsible for making the CXX_C integration
add_library(SquareRoot_CXX_C_ADAPTER SHARED SquareRoot_C_Adapter.cpp SquareRoot.cpp)
# Set the compile flags
set_property(TARGET SquareRoot_CXX_C_ADAPTER PROPERTY COMPILE_FLAGS ${CXXFLAGS_O0})

# Build and link the SquareRoot module
add_library(SquareRoot SHARED sqrtlib.c c_square_root.c)

# Link the library with the Python's dependency
target_link_libraries(SquareRoot ${PYTHON_LIBRARIES})

# Tweaks the name of the library to match what Python expects
set_target_properties(SquareRoot PROPERTIES SUFFIX .so)
set_target_properties(SquareRoot PROPERTIES PREFIX "")

# Copy the Python's main file to the library directory
file(COPY python/main.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})