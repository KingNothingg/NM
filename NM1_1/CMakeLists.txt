cmake_minimum_required(VERSION 3.21)
project(NM1)

set(CMAKE_CXX_STANDARD 14)

add_executable(NM1 main.cpp matrix.cpp lu.cpp)
