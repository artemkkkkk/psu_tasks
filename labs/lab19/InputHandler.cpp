#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <random>
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

std::vector<int> InputHandler::inputBinaryDataFromConsole() {
    std::string input;
    std::cout << "Введите бинарные данные (0 и 1 через пробел): ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, input);
    
    std::vector<int> data;
    std::istringstream iss(input);
    int bit;
    while (iss >> bit) {
        if (bit != 0 && bit != 1) {
            throw std::invalid_argument("Данные должны содержать только 0 и 1");
        }
        data.push_back(bit);
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Пустые данные");
    }
    
    return data;
}

std::vector<int> InputHandler::inputBinaryDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::vector<int> data;
    int bit;
    while (file >> bit) {
        if (bit != 0 && bit != 1) {
            throw std::runtime_error("Файл содержит некорректные данные");
        }
        data.push_back(bit);
    }
    
    if (data.empty()) {
        throw std::runtime_error("Файл пуст");
    }
    
    return data;
}

std::vector<int> InputHandler::generateRandomBinaryData(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    std::vector<int> data;
    for (int i = 0; i < count; ++i) {
        data.push_back(dis(gen));
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
    std::getline(file, text, '\0');
    
    if (!Validator::isValidText(text)) {
        throw std::runtime_error("Файл пуст");
    }
    
    return text;
}

std::string InputHandler::generateRandomText() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> lengthDis(10, 50);
    std::uniform_int_distribution<> charDis(0, 25);
    
    int length = lengthDis(gen);
    std::string text;
    for (int i = 0; i < length; ++i) {
        text += 'a' + charDis(gen);
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