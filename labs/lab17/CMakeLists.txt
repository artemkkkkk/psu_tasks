cmake_minimum_required(VERSION 4.0)
project(lab17)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab17 main.cpp
        TreeNode.h
        TreeNode.cpp
        ExpressionTree.h
        ExpressionTree.cpp
        CalcTree1.h
        CalcTree1.cpp
        CalcTree23.h
        CalcTree23.cpp
        Validator.h
        Validator.cpp
        InputHandler.h
        InputHandler.cpp
        DynamicArray.h
        Stack.h)
