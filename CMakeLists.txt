cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (ibl_stats)

file(GLOB_RECURSE sources src/*.cpp src/*.h)

add_executable(stats ${sources})