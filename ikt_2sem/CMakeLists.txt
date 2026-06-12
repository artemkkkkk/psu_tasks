cmake_minimum_required(VERSION 4.0)
project(ikt_2sem)

set(CMAKE_CXX_STANDARD 20)

add_executable(ikt_2sem
        main.cpp
        exceptions.h
        stack.h
        expression_converter.h
        expression_converter.cpp
        menu.h
        menu.cpp
)
