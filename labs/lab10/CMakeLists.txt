cmake_minimum_required(VERSION 4.0)
project(lab10)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab10 main.cpp
        stack.cpp
        stack.h
        queue.cpp
        queue.h
        list.cpp
        list.h)
