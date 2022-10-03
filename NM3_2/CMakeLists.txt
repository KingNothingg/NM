cmake_minimum_required(VERSION 3.22)
project(NM3_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(NM3_2 main.cpp spline.h tridiag.cpp)
