cmake_minimum_required(VERSION 4.0)
project(lab19)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab19 main.cpp
        menu.h
        menu.cpp
        utils.h
        utils.cpp
        utf8.h
        utf8.cpp
        hamming.h
        hamming.cpp
        huffman.h
        huffman.cpp
        vigenere.h
        vigenere.cpp
        task1.h
        task1.cpp
        task2.h
        task2.cpp
        task3.h
        task3.cpp)
