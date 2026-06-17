cmake_minimum_required(VERSION 4.0)
project(lab19)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab19 main.cpp
        HammingCode.h
        HammingCode.cpp
        HuffmanNode.h
        HuffmanNode.cpp
        HuffmanCode.h
        HuffmanCode.cpp
        VigenereCipher.h
        VigenereCipher.cpp
        Validator.h
        Validator.cpp
        InputHandler.h
        InputHandler.cpp)
