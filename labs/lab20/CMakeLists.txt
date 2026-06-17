cmake_minimum_required(VERSION 4.0)
project(lab20)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab20 main.cpp
        Time.h
        Time.cpp
        Validator.h
        Validator.cpp
        InputHandler.h
        InputHandler.cpp)
