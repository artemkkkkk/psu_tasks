#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <random>
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
            return std::stoi(input);
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
            return std::stoi(input);
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

std::vector<int> InputHandler::inputFromConsole() {
    int count = readValidPositiveInteger("Введите количество элементов дерева: ");
    std::vector<int> values;
    for (int i = 0; i < count; ++i) {
        int value = readValidInteger("Введите значение элемента " + std::to_string(i + 1) + ": ");
        values.push_back(value);
    }
    return values;
}

std::vector<int> InputHandler::inputFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    std::vector<int> values;
    int value;
    while (file >> value) {
        values.push_back(value);
    }
    if (values.empty()) {
        throw std::runtime_error("Файл пуст или содержит некорректные данные");
    }
    return values;
}

std::vector<int> InputHandler::generateRandom(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    std::vector<int> values;
    for (int i = 0; i < count; ++i) {
        values.push_back(dis(gen));
    }
    return values;
}