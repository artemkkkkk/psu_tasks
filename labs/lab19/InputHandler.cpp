#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <sstream>

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
        try {
            return std::stoi(input);
        } catch (...) {
            std::cout << "Некорректное целое число. Попробуйте снова." << std::endl;
        }
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

DynamicArray<int> InputHandler::inputBinaryDataFromConsole() {
    std::string input;
    std::cout << "Введите бинарные данные (0 и 1 через пробел): ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, input);

    DynamicArray<int> data;
    std::istringstream iss(input);
    int bit;
    while (iss >> bit) {
        if (!Validator::isValidBinaryBit(bit)) {
            throw std::invalid_argument("Данные должны содержать только 0 и 1");
        }
        data.pushBack(bit);
    }

    if (data.isEmpty()) {
        throw std::invalid_argument("Пустые данные");
    }

    return data;
}

DynamicArray<int> InputHandler::inputBinaryDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    DynamicArray<int> data;
    int bit;
    while (file >> bit) {
        if (!Validator::isValidBinaryBit(bit)) {
            throw std::runtime_error("Файл содержит некорректные данные");
        }
        data.pushBack(bit);
    }

    if (data.isEmpty()) {
        throw std::runtime_error("Файл пуст");
    }

    return data;
}

DynamicArray<int> InputHandler::generateRandomBinaryData(int count) {
    DynamicArray<int> data;
    for (int i = 0; i < count; ++i) {
        data.pushBack(rand() % 2);
    }
    return data;
}

std::string InputHandler::inputTextFromConsole() {
    std::string text;
    std::cout << "Введите текст: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, text);

    if (!Validator::isValidText(text)) {
        throw std::invalid_argument("Пустой текст");
    }

    return text;
}

std::string InputHandler::inputTextFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::string text;
    std::string line;
    while (std::getline(file, line)) {
        if (!text.empty()) {
            text += "\n";
        }
        text += line;
    }

    if (!Validator::isValidText(text)) {
        throw std::runtime_error("Файл пуст");
    }

    return text;
}

std::string InputHandler::generateRandomText() {
    int length = rand() % 41 + 10;
    std::string text;
    for (int i = 0; i < length; ++i) {
        text += static_cast<char>('a' + rand() % 26);
    }
    return text;
}

std::string InputHandler::inputKeyFromConsole() {
    std::string key;
    std::cout << "Введите ключ (только буквы): ";
    std::cin >> key;

    if (!Validator::isValidKey(key)) {
        throw std::invalid_argument("Ключ должен содержать только буквы");
    }

    return key;
}

std::string InputHandler::inputKeyFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::string key;
    file >> key;

    if (!Validator::isValidKey(key)) {
        throw std::runtime_error("Ключ должен содержать только буквы");
    }

    return key;
}