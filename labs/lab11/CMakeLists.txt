cmake_minimum_required(VERSION 4.0)
project(lab11)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab11 main.cpp
        dlist.cpp
        dlist.h
        clist.cpp
        clist.h
        counting_game.cpp
        counting_game.h)
