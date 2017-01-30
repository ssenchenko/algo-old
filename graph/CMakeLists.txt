cmake_minimum_required(VERSION 3.6)
project(graph)

set(CMAKE_CXX_STANDARD 11)

include_directories(../utils)

set(SOURCE_FILES main.cpp ../utils/myutil.cpp graph.hpp graph.cpp tests.h tests.cpp union-find.hpp)
add_executable(graph ${SOURCE_FILES})