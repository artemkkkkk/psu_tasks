#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <stdexcept>

int InputHandler::readValidPositiveInteger(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода. Попробуйте снова." << std::endl;
            continue;
        }
        if (Validator::isValidPositiveInteger(input)) {
            return std::atoi(input.c_str());
        }
        std::cout << "Некорректное положительное целое число. Попробуйте снова." << std::endl;
    }
}

int InputHandler::readValidNonNegativeInteger(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода. Попробуйте снова." << std::endl;
            continue;
        }
        if (Validator::isValidNonNegativeInteger(input)) {
            return std::atoi(input.c_str());
        }
        std::cout << "Некорректное неотрицательное целое число. Попробуйте снова." << std::endl;
    }
}

int InputHandler::readValidVertexNumber(const std::string& prompt, int vertexCount) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода. Попробуйте снова." << std::endl;
            continue;
        }
        if (Validator::isValidPositiveInteger(input)) {
            int value = std::atoi(input.c_str());
            if (Validator::isValidVertexNumber(value, vertexCount)) {
                return value;
            }
        }
        std::cout << "Номер вершины должен быть от 1 до " << vertexCount << ". Попробуйте снова." << std::endl;
    }
}

double InputHandler::readValidDensity(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода. Попробуйте снова." << std::endl;
            continue;
        }
        if (Validator::isValidDensity(value)) {
            return value;
        }
        std::cout << "Плотность должна быть от 0.0 до 1.0. Попробуйте снова." << std::endl;
    }
}

std::string InputHandler::readValidFilename(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (Validator::isValidFilename(input)) {
            return input;
        }
        std::cout << "Некорректное имя файла. Попробуйте снова." << std::endl;
    }
}