cmake_minimum_required(VERSION 2.8)

project(CPP_PYTHON_INTEGRATION)

# For development, only,
# Comment the next line after the project is working properly
# set(CMAKE_VERBOSE_MAKEFILE on)

# Set the reference standard of the C++ Language
set(CMAKE_CXX_STANDARD 11)

### Library configuration

# Remove the "lib" prefix from all the ".so" files
set(CMAKE_SHARED_LIBRARY_PREFIX  "")

# The ".so" suffix is the standard,
# but for the sake of complitude
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

### Flags
# No optimization flag
set(CXXFLAGS_O0 "-O0")
# Maximum compiler auto optimization flag
set(CXXFLAGS_SSE2 "-O3 -march=native")

### Build

# Create the SquareRoot.so artifact
add_library(SquareRoot SHARED SquareRoot.cpp)

# Set up a compile flag for the SquareRoot.so artifact
set_property(TARGET SquareRoot PROPERTY COMPILE_FLAGS ${CXXFLAGS_O0})

# Create the SquareRoot_C_Adapter.so artifact
add_library(SquareRoot_C_Adapter SHARED SquareRoot_C_Adapter.cpp)

# Link the two libraries, so they can be used later,
target_link_libraries(SquareRoot_C_Adapter SquareRoot)

# Create the C_SquareRoot.so artifact
add_library(C_SquareRoot SHARED c_square_root.c)

# Link the C_SquareRoot lib with the SquareRoot_C_Adapter lib
target_link_libraries(C_SquareRoot SquareRoot_C_Adapter)

# Set the Python version to default in the OS
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(SquarePy SHARED sqrtlib.c)

target_link_libraries(SquarePy C_SquareRoot ${PYTHON_LIBRARIES})

### Debug

# main.py
# Copy the Python's main file to the library directory
file(COPY debug/main.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# main.c
add_executable(main debug/main.c)
target_link_libraries(main C_SquareRoot)