cmake_minimum_required(VERSION 4.0)
project(lab18)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab18 main.cpp
        menu.h
        menu.cpp
        utils.h
        utils.cpp
        tnode.h
        tnode.cpp
        binarytree.h
        binarytree.cpp
        treeinput.h
        treeinput.cpp
        inorderiterator.h
        inorderiterator.cpp
        treefun1.h
        treefun1.cpp
        treefun3.h
        treefun3.cpp
        treefun11.h
        treefun11.cpp)
