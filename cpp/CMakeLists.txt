cmake_minimum_required(VERSION 2.8)

project(CPP_PYTHON_INTEGRATION)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 11)

set(CXXFLAGS_O0 "-O0")
set(CXXFLAGS_SSE2 "-O3 -march=native")

# Set the Python version to 2.7
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Build and link the SquareRoot module
add_library(SquareRoot SHARED sqrtlib.cpp SquareRoot.cpp)

set_property(TARGET SquareRoot PROPERTY COMPILE_FLAGS ${CXXFLAGS_O0})

target_link_libraries(SquareRoot ${PYTHON_LIBRARIES})

# Tweaks the name of the library to match what Python expects
set_target_properties(SquareRoot PROPERTIES SUFFIX .so)
set_target_properties(SquareRoot PROPERTIES PREFIX "")