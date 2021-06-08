cmake_minimum_required(VERSION 3.0.0)
project(ex3 VERSION 0.1.0)

set(CMAKE_CXX_STANDART 11)
set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -g")
set(MTM_FLAGS_RELEASE "{MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(hw2_wet UnionFind.h dynamic_array.h test_main.cpp exceptions.h)