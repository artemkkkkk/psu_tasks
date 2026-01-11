cmake_minimum_required(VERSION 4.0)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab5 main.cpp
        string_tasks.cpp
        string_tasks.h
        password_gen.cpp
        password_gen.h
        checker.cpp
        checker.h)
