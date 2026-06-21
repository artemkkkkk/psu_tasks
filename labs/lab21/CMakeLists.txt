cmake_minimum_required(VERSION 4.0)
project(lab21)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab21 main.cpp
        Graph.h
        Graph.cpp
        UndirectedGraph.h
        UndirectedGraph.cpp
        DirectedGraph.h
        DirectedGraph.cpp
        Validator.h
        Validator.cpp
        InputHandler.h
        InputHandler.cpp
        DynamicArray.h
        Queue.h)
