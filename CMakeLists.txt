project(Geno)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -O0")

add_subdirectory("src")
add_subdirectory("sample")
add_subdirectory("test")
