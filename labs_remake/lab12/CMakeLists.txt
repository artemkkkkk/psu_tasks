cmake_minimum_required(VERSION 4.0)
project(lab12)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab12 main.cpp
        menu.h
        menu.cpp
        utils.h
        utils.cpp
        stlprint.h
        stl2seq5.h
        stl2seq5.cpp
        stl2seq8.h
        stl2seq8.cpp
        stl2seq34.h
        stl2seq34.cpp
        stl1iter8.h
        stl1iter8.cpp)
