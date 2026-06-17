#include "InputHandler.h"
#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>

Point InputHandler::inputPointFromConsole() {
    double x, y;
    std::cout << "Введите координату X: ";
    if (!(std::cin >> x)) {
        throw std::invalid_argument("Некорректный ввод координаты X");
    }
    std::cout << "Введите координату Y: ";
    if (!(std::cin >> y)) {
        throw std::invalid_argument("Некорректный ввод координаты Y");
    }
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
    
    std::vector<int> grades;
    int gradeCount;
    std::cout << "Введите количество оценок: ";
    if (!(std::cin >> gradeCount) || gradeCount < 0) {
        throw std::invalid_argument("Некорректное количество оценок");
    }
    
    for (int i = 0; i < gradeCount; ++i) {
        int grade;
        std::cout << "Введите оценку " << (i + 1) << ": ";
        if (!(std::cin >> grade) || grade < 2 || grade > 5) {
            throw std::invalid_argument("Оценка должна быть от 2 до 5");
        }
        grades.push_back(grade);
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
    
    std::vector<int> grades;
    int grade;
    while (file >> grade) {
        if (grade < 2 || grade > 5) {
            throw std::runtime_error("Оценка должна быть от 2 до 5");
        }
        grades.push_back(grade);
    }
    
    return Student(name, grades);
}

Point InputHandler::generateRandomPoint() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);
    return Point(dis(gen), dis(gen));
}

Line InputHandler::generateRandomLine() {
    return Line(generateRandomPoint(), generateRandomPoint());
}

Student InputHandler::generateRandomStudent() {
    return Student(generateRandomName(), generateRandomGrades());
}

std::string InputHandler::generateRandomName() {
    std::vector<std::string> names = {"Вася", "Петя", "Коля", "Маша", "Даша", "Саша"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, names.size() - 1);
    return names[dis(gen)];
}

std::vector<int> InputHandler::generateRandomGrades() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> countDis(1, 5);
    std::uniform_int_distribution<> gradeDis(2, 5);
    
    std::vector<int> grades;
    int count = countDis(gen);
    for (int i = 0; i < count; ++i) {
        grades.push_back(gradeDis(gen));
    }
    return grades;
}