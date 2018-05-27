cmake_minimum_required(VERSION 2.8)
include(ExternalProject)

# Adding customized cmake module for building boost
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(CPP_PYTHON_INTEGRATION)

# Find default python libraries and interpreter
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
include(BuildBoost) # Custom module

include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})

# Build and link the pylib module
add_library(sqrtlib SHARED sqrtlib.cpp)
target_link_libraries(sqrtlib ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
add_dependencies(sqrtlib Boost)

# Tweaks the name of the library to match what Python expects
set_target_properties(sqrtlib PROPERTIES SUFFIX .so)
set_target_properties(sqrtlib PROPERTIES PREFIX "")