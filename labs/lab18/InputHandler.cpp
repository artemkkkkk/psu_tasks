#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

int InputHandler::readValidInteger(const std::string& prompt) {
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
        if (Validator::isValidInteger(input)) {
            return std::atoi(input.c_str());
        }
        std::cout << "Некорректное целое число. Попробуйте снова." << std::endl;
    }
}

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

DynamicArray<int> InputHandler::inputFromConsole() {
    int count = readValidPositiveInteger("Введите количество элементов дерева: ");
    DynamicArray<int> values;
    for (int i = 0; i < count; ++i) {
        int value = readValidInteger("Введите значение элемента " + std::to_string(i + 1) + ": ");
        values.pushBack(value);
    }
    return values;
}

DynamicArray<int> InputHandler::inputFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    DynamicArray<int> values;
    int value;
    while (file >> value) {
        values.pushBack(value);
    }
    if (values.isEmpty()) {
        throw std::runtime_error("Файл пуст или содержит некорректные данные");
    }
    return values;
}

DynamicArray<int> InputHandler::generateRandom(int count) {
    DynamicArray<int> values;
    for (int i = 0; i < count; ++i) {
        values.pushBack(rand() % 100 + 1);
    }
    return values;
}