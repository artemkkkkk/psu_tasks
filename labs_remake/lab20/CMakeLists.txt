cmake_minimum_required(VERSION 4.0)
project(lab20)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab20 main.cpp
        menu.h
        menu.cpp
        utils.h
        utils.cpp
        time.h
        time.cpp
        timeinput.h
        timeinput.cpp
        task1.h
        task1.cpp
        task2.h
        task2.cpp)
