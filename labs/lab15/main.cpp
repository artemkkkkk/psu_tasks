#ifdef _WIN32
#include <windows.h>
#endif

#include "Point.h"
#include "Line.h"
#include "Student.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <stdexcept>

void demonstrateTask1() {
    std::cout << "\n=== Задача 1: Точка координат ===" << std::endl;

    Point p1(3, 5);
    Point p2(25, 6);
    Point p3(7, 8);

    std::cout << "Точка 1: " << p1.toString() << std::endl;
    std::cout << "Точка 2: " << p2.toString() << std::endl;
    std::cout << "Точка 3: " << p3.toString() << std::endl;
}

void demonstrateTask2() {
    std::cout << "\n=== Задача 2: Линия ===" << std::endl;

    Line line1(Point(1, 3), Point(23, 8));
    Line line2(Point(5, 10), Point(25, 10));

    std::cout << "Линия 1: " << line1.toString() << std::endl;
    std::cout << "Линия 2: " << line2.toString() << std::endl;

    Line line3(line1.getStart(), line2.getEnd());
    std::cout << "Линия 3: " << line3.toString() << std::endl;

    line1.setStart(Point(2, 4));
    line2.setEnd(Point(30, 15));
    line3.setStart(line1.getStart());
    line3.setEnd(line2.getEnd());

    std::cout << "\nПосле изменения:" << std::endl;
    std::cout << "Линия 1: " << line1.toString() << std::endl;
    std::cout << "Линия 2: " << line2.toString() << std::endl;
    std::cout << "Линия 3: " << line3.toString() << std::endl;
}

void demonstrateTask3() {
    std::cout << "\n=== Задача 3: Студент ===" << std::endl;

    DynamicArray<int> vasyaGrades;
    vasyaGrades.pushBack(3);
    vasyaGrades.pushBack(4);
    vasyaGrades.pushBack(5);

    Student vasya("Вася", vasyaGrades);
    std::cout << "Вася: " << vasya.toString() << std::endl;

    Student petya = vasya;
    petya.setName("Петя");
    petya.setGrade(0, 5);

    std::cout << "Петя (после копирования и изменения): " << petya.toString() << std::endl;
    std::cout << "Вася (не изменился): " << vasya.toString() << std::endl;

    Student andrey("Андрей");
    andrey.setGrades(vasya.getGrades());
    std::cout << "Андрей (независимая копия): " << andrey.toString() << std::endl;
}

void demonstrateTask4() {
    std::cout << "\n=== Задача 4: Создаем Точку и Линию ===" << std::endl;

    Point p1(3, 5);
    Point p2(25, 6);
    Point p3(7, 8);

    std::cout << "Точка 1: " << p1.toString() << std::endl;
    std::cout << "Точка 2: " << p2.toString() << std::endl;
    std::cout << "Точка 3: " << p3.toString() << std::endl;

    Line line1(Point(1, 3), Point(23, 8));
    Line line2(5, 10, 25, 10);

    std::cout << "Линия 1: " << line1.toString() << std::endl;
    std::cout << "Линия 2: " << line2.toString() << std::endl;
}

void demonstrateTask5() {
    std::cout << "\n=== Задача 5: Длина Линии ===" << std::endl;

    Line line(Point(1, 1), Point(10, 15));
    std::cout << "Линия: " << line.toString() << std::endl;
    std::cout << "Длина линии: " << line.getLength() << std::endl;
}

void interactivePointDemo() {
    std::cout << "\n=== Интерактивная демонстрация Точки ===" << std::endl;
    std::cout << "1. Ввод из консоли" << std::endl;
    std::cout << "2. Ввод из файла" << std::endl;
    std::cout << "3. Случайная генерация" << std::endl;
    std::cout << "0. Назад" << std::endl;

    int choice;
    std::cout << "Выберите способ ввода: ";
    std::cin >> choice;

    try {
        Point point;
        switch (choice) {
            case 1:
                point = InputHandler::inputPointFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                point = InputHandler::inputPointFromFile(filename);
                break;
            }
            case 3:
                point = InputHandler::generateRandomPoint();
                break;
            case 0:
                return;
            default:
                std::cout << "Неверный выбор" << std::endl;
                return;
        }
        std::cout << "Созданная точка: " << point.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void interactiveLineDemo() {
    std::cout << "\n=== Интерактивная демонстрация Линии ===" << std::endl;
    std::cout << "1. Ввод из консоли" << std::endl;
    std::cout << "2. Ввод из файла" << std::endl;
    std::cout << "3. Случайная генерация" << std::endl;
    std::cout << "0. Назад" << std::endl;

    int choice;
    std::cout << "Выберите способ ввода: ";
    std::cin >> choice;

    try {
        Line line;
        switch (choice) {
            case 1:
                line = InputHandler::inputLineFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                line = InputHandler::inputLineFromFile(filename);
                break;
            }
            case 3:
                line = InputHandler::generateRandomLine();
                break;
            case 0:
                return;
            default:
                std::cout << "Неверный выбор" << std::endl;
                return;
        }
        std::cout << "Созданная линия: " << line.toString() << std::endl;
        std::cout << "Длина линии: " << line.getLength() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void interactiveStudentDemo() {
    std::cout << "\n=== Интерактивная демонстрация Студента ===" << std::endl;
    std::cout << "1. Ввод из консоли" << std::endl;
    std::cout << "2. Ввод из файла" << std::endl;
    std::cout << "3. Случайная генерация" << std::endl;
    std::cout << "0. Назад" << std::endl;

    int choice;
    std::cout << "Выберите способ ввода: ";
    std::cin >> choice;

    try {
        Student student;
        switch (choice) {
            case 1:
                student = InputHandler::inputStudentFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                student = InputHandler::inputStudentFromFile(filename);
                break;
            }
            case 3:
                student = InputHandler::generateRandomStudent();
                break;
            case 0:
                return;
            default:
                std::cout << "Неверный выбор" << std::endl;
                return;
        }
        std::cout << "Созданный студент: " << student.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    srand(static_cast<unsigned>(time(nullptr)));

    int choice;
    do {
        std::cout << "\n========== МЕНЮ ==========" << std::endl;
        std::cout << "1. Демонстрация Задачи 1 (Точка)" << std::endl;
        std::cout << "2. Демонстрация Задачи 2 (Линия)" << std::endl;
        std::cout << "3. Демонстрация Задачи 3 (Студент)" << std::endl;
        std::cout << "4. Демонстрация Задачи 4 (Создаем Точку и Линию)" << std::endl;
        std::cout << "5. Демонстрация Задачи 5 (Длина Линии)" << std::endl;
        std::cout << "6. Интерактивная работа с Точкой" << std::endl;
        std::cout << "7. Интерактивная работа с Линией" << std::endl;
        std::cout << "8. Интерактивная работа со Студентом" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Выберите пункт меню: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
            continue;
        }

        if (!Validator::isValidMenuChoice(choice, 8)) {
            std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                demonstrateTask1();
                break;
            case 2:
                demonstrateTask2();
                break;
            case 3:
                demonstrateTask3();
                break;
            case 4:
                demonstrateTask4();
                break;
            case 5:
                demonstrateTask5();
                break;
            case 6:
                interactivePointDemo();
                break;
            case 7:
                interactiveLineDemo();
                break;
            case 8:
                interactiveStudentDemo();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}