#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

double InputHandler::readValidDouble(const std::string& prompt) {
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
        if (Validator::isValidDouble(input)) {
            return std::atof(input.c_str());
        }
        std::cout << "Некорректное число. Попробуйте снова." << std::endl;
    }
}

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

Point InputHandler::inputPointFromConsole() {
    double x = readValidDouble("Введите координату X: ");
    double y = readValidDouble("Введите координату Y: ");
    return Point(x, y);
}

Line InputHandler::inputLineFromConsole() {
    std::cout << "Введите начальную точку:" << std::endl;
    Point start = inputPointFromConsole();
    std::cout << "Введите конечную точку:" << std::endl;
    Point end = inputPointFromConsole();
    return Line(start, end);
}

Student InputHandler::inputStudentFromConsole() {
    std::string name;
    std::cout << "Введите имя студента: ";
    std::cin >> name;

    int gradeCount = readValidInteger("Введите количество оценок: ");
    if (!Validator::isValidGradeCount(gradeCount)) {
        throw std::invalid_argument("Некорректное количество оценок");
    }

    DynamicArray<int> grades;
    for (int i = 0; i < gradeCount; ++i) {
        int grade;
        while (true) {
            std::cout << "Введите оценку " << (i + 1) << ": ";
            std::cin >> grade;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Ошибка ввода. Попробуйте снова." << std::endl;
                continue;
            }
            if (Validator::isValidGrade(grade)) {
                break;
            }
            std::cout << "Оценка должна быть от 2 до 5. Попробуйте снова." << std::endl;
        }
        grades.pushBack(grade);
    }

    return Student(name, grades);
}

Point InputHandler::inputPointFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    double x, y;
    if (!(file >> x >> y)) {
        throw std::runtime_error("Некорректный формат файла");
    }

    return Point(x, y);
}

Line InputHandler::inputLineFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    double x1, y1, x2, y2;
    if (!(file >> x1 >> y1 >> x2 >> y2)) {
        throw std::runtime_error("Некорректный формат файла");
    }

    return Line(x1, y1, x2, y2);
}

Student InputHandler::inputStudentFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::string name;
    if (!(file >> name)) {
        throw std::runtime_error("Некорректный формат файла");
    }

    DynamicArray<int> grades;
    int grade;
    while (file >> grade) {
        if (!Validator::isValidGrade(grade)) {
            throw std::runtime_error("Оценка должна быть от 2 до 5");
        }
        grades.pushBack(grade);
    }

    return Student(name, grades);
}

Point InputHandler::generateRandomPoint() {
    srand(static_cast<unsigned>(time(nullptr)));
    double x = (rand() % 20000 - 10000) / 100.0;
    double y = (rand() % 20000 - 10000) / 100.0;
    return Point(x, y);
}

Line InputHandler::generateRandomLine() {
    return Line(generateRandomPoint(), generateRandomPoint());
}

Student InputHandler::generateRandomStudent() {
    return Student(generateRandomName(), generateRandomGrades());
}

std::string InputHandler::generateRandomName() {
    const char* names[] = {"Вася", "Петя", "Коля", "Маша", "Даша", "Саша"};
    int index = rand() % 6;
    return std::string(names[index]);
}

DynamicArray<int> InputHandler::generateRandomGrades() {
    DynamicArray<int> grades;
    int count = rand() % 5 + 1;
    for (int i = 0; i < count; ++i) {
        grades.pushBack(rand() % 4 + 2);
    }
    return grades;
}