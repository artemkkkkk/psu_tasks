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
        try {
            return std::stoi(input);
        } catch (...) {
            std::cout << "Некорректное целое число. Попробуйте снова." << std::endl;
        }
    }
}

unsigned int InputHandler::readValidUnsignedInt(const std::string& prompt) {
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
        if (Validator::isValidUnsignedInt(input)) {
            return static_cast<unsigned int>(std::stoul(input));
        }
        std::cout << "Некорректное беззнаковое целое число. Попробуйте снова." << std::endl;
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

Time InputHandler::inputTimeFromConsole() {
    int hours = readValidInteger("Введите часы (0-23): ");
    if (!Validator::isValidHours(hours)) {
        throw std::invalid_argument("Часы должны быть в диапазоне 0-23");
    }
    int minutes = readValidInteger("Введите минуты (0-59): ");
    if (!Validator::isValidMinutes(minutes)) {
        throw std::invalid_argument("Минуты должны быть в диапазоне 0-59");
    }
    return Time(static_cast<unsigned char>(hours), static_cast<unsigned char>(minutes));
}

Time InputHandler::inputTimeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    int hours, minutes;
    if (!(file >> hours >> minutes)) {
        throw std::runtime_error("Некорректный формат файла");
    }
    if (!Validator::isValidHours(hours) || !Validator::isValidMinutes(minutes)) {
        throw std::runtime_error("Некорректные значения времени в файле");
    }
    return Time(static_cast<unsigned char>(hours), static_cast<unsigned char>(minutes));
}

Time InputHandler::generateRandomTime() {
    int hours = rand() % 24;
    int minutes = rand() % 60;
    return Time(static_cast<unsigned char>(hours), static_cast<unsigned char>(minutes));
}

unsigned int InputHandler::inputMinutesFromConsole(const std::string& prompt) {
    return readValidUnsignedInt(prompt);
}

unsigned int InputHandler::inputMinutesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    unsigned int minutes;
    if (!(file >> minutes)) {
        throw std::runtime_error("Некорректный формат файла");
    }
    return minutes;
}

unsigned int InputHandler::generateRandomMinutes() {
    return static_cast<unsigned int>(rand() % 1440);
}