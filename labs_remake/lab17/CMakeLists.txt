cmake_minimum_required(VERSION 4.0)
project(lab17)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab17 main.cpp
        menu.h
        menu.cpp
        utils.h
        utils.cpp
        tnode.h
        tnode.cpp
        calctree.h
        calctree.cpp
        treechecker.h
        treechecker.cpp
        calctree1.h
        calctree1.cpp
        calctree23.h
        calctree23.cpp)
