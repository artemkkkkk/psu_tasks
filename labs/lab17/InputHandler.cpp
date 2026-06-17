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
        if (Validator::isValidInteger(input)) {
            return std::stoi(input);
        }
        std::cout << "Некорректное целое число. Попробуйте снова." << std::endl;
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

std::string InputHandler::inputExpressionFromConsole() {
    std::string expression;
    std::cout << "Введите выражение: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, expression);
    if (!Validator::isValidExpression(expression)) {
        throw std::invalid_argument("Пустое выражение");
    }
    return expression;
}

std::string InputHandler::inputExpressionFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    std::string expression;
    std::getline(file, expression);
    if (!Validator::isValidExpression(expression)) {
        throw std::runtime_error("Файл пуст или содержит некорректные данные");
    }
    return expression;
}

std::string InputHandler::generateRandomExpression() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> numDis(1, 9);
    std::uniform_int_distribution<> opDis(0, 2);
    std::string ops[] = {"+", "-", "*"};
    
    std::ostringstream oss;
    oss << numDis(gen) << " " << numDis(gen) << " " << ops[opDis(gen)] << " " << numDis(gen) << " " << ops[opDis(gen)];
    return oss.str();
}