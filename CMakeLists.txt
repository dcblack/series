#!cmake -B build

cmake_minimum_required (VERSION 3.1)
project(series LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to build all targets. Supported values are 98, 11, and 14.")

add_executable(series series_test.cpp)

add_executable(coord coord_test.cpp)

# vim:nospell:syntax=cmake
