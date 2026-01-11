cmake_minimum_required(VERSION 4.0)
project(magic_square)

set(CMAKE_CXX_STANDARD 20)

add_executable(magic_square src/main.cpp
        src/magic_square.cpp
        src/file_io.cpp
        include/magic_square.h
        include/file_io.h)
