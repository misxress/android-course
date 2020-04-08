cmake_minimum_required(VERSION 3.15)
project(compression)

set(CMAKE_CXX_STANDARD 14)

add_executable(compression bmp.h bmp.cpp lzw.h lzw.cpp txt.h txt.cpp test.cpp)