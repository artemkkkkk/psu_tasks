cmake_minimum_required(VERSION 4.0)
project(lab15)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab15 main.cpp
        Point.h
        Point.cpp
        Line.h
        Line.cpp
        Student.h
        Student.cpp
        InputHandler.h
        InputHandler.cpp
        DynamicArray.h
        Stack.h
        Queue.h
        Queue.cpp
        Validator.h
        Validator.cpp)
