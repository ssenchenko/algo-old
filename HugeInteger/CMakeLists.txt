cmake_minimum_required(VERSION 3.6)
project(HugeInteger)

set(CMAKE_CXX_STANDARD 11)

include_directories(../utils)

set(SOURCE_FILES main.cpp ../utils/myutil.cpp HugeInteger.cpp HugeInteger.hpp)
add_executable(HugeInteger ${SOURCE_FILES})