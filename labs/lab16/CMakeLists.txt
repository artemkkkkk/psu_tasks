cmake_minimum_required(VERSION 4.0)
project(lab16)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab16 main.cpp
        TreeNode.h
        TreeNode.cpp
        BinaryTree.h
        BinaryTree.cpp
        Validator.h
        Validator.cpp
        InputHandler.h
        InputHandler.cpp)
