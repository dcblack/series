# CMakeLists.txt -- Top-level CMake script

cmake_minimum_required (VERSION 3.1)
project (series CXX C)

include_directories (/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/)

set (CMAKE_CXX_STANDARD 14 CACHE STRING
     "C++ standard to build all targets. Supported values are 98, 11, and 14.")

add_executable(series series.cpp)
