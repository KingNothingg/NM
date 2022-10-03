cmake_minimum_required(VERSION 3.22)
project(NM3_5)

set(CMAKE_CXX_STANDARD 14)

add_executable(NM3_5 main.cpp interpolation.h polynom.h integrate.h)
