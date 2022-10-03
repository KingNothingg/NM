cmake_minimum_required(VERSION 3.22)
project(NM3_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(NM3_3 main.cpp lu.cpp matrix.cpp polynom.h MNK.h)
