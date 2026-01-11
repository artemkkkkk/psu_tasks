cmake_minimum_required(VERSION 4.0)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        while_tasks.cpp
        while_tasks.h
        series_tasks.cpp
        series_tasks.h
        fun_tasks.cpp
        fun_tasks.h)
