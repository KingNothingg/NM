cmake_minimum_required(VERSION 3.22)
project(NM4_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(NM4_2 main.cpp solver.h tridiag.cpp desolve.h utils.h)
