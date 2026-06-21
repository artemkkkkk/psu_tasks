#ifdef _WIN32
#include <windows.h>
#endif

#include "CalcTree1.h"
#include "CalcTree23.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ctime>

std::string getInputExpression(const std::string& taskName) {
    std::cout << "\n=== Ввод данных для " << taskName << " ===" << std::endl;
    std::cout << "1. Ввод из консоли" << std::endl;
    std::cout << "2. Ввод из файла" << std::endl;
    std::cout << "3. Случайная генерация" << std::endl;
    std::cout << "0. Назад" << std::endl;

    int choice;
    std::cout << "Выберите способ ввода: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::invalid_argument("Некорректный ввод");
    }

    switch (choice) {
        case 1:
            return InputHandler::inputExpressionFromConsole();
        case 2: {
            std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
            return InputHandler::inputExpressionFromFile(filename);
        }
        case 3:
            return InputHandler::generateRandomExpression();
        case 0:
            return "";
        default:
            throw std::invalid_argument("Неверный выбор");
    }
}

void task1CalcTree1() {
    std::cout << "\n========== CalcTree1: Убрать вычитания ==========" << std::endl;

    try {
        std::string expression = getInputExpression("CalcTree1 (постфиксная запись)");
        if (expression.empty()) {
            return;
        }

        CalcTree1 tree;
        tree.buildFromPostfix(expression);

        std::cout << "\nИсходное дерево:" << std::endl;
        tree.printGraphical(std::cout);

        tree.transform();

        std::cout << "\nДерево после преобразования:" << std::endl;
        tree.printGraphical(std::cout);

        std::cout << "\nРезультат вычисления: " << tree.calculate(0) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task2CalcTree23() {
    std::cout << "\n========== CalcTree23: Коммутативность сложения ==========" << std::endl;

    try {
        std::string expression = getInputExpression("CalcTree23 (инфиксная запись)");
        if (expression.empty()) {
            return;
        }

        int xValue = InputHandler::readValidInteger("Введите значение переменной x: ");

        CalcTree23 tree;
        tree.buildFromInfix(expression);

        std::cout << "\nИсходное дерево:" << std::endl;
        tree.printGraphical(std::cout);

        std::cout << "\nЗначение выражения при x=" << xValue << ": " << tree.calculate(xValue) << std::endl;

        tree.transform();

        std::cout << "\nДерево после преобразования:" << std::endl;
        tree.printGraphical(std::cout);

        std::string outputFilename = InputHandler::readValidFilename("Введите имя файла для вывода (FN2): ");
        std::ofstream outFile(outputFilename);
        if (!outFile.is_open()) {
            throw std::runtime_error("Не удалось создать файл: " + outputFilename);
        }

        outFile << "Префиксная запись: " << tree.getPrefixNotation() << std::endl;
        outFile << "Постфиксная запись: " << tree.getPostfixNotation() << std::endl;
        outFile << "Инфиксная запись: " << tree.getInfixNotation() << std::endl;

        std::cout << "\nРезультаты записаны в файл: " << outputFilename << std::endl;
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
        std::cout << "\n==================== МЕНЮ ====================" << std::endl;
        std::cout << "1. CalcTree1: Убрать вычитания из постфиксного выражения" << std::endl;
        std::cout << "2. CalcTree23: Коммутативность сложения в инфиксном выражении" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "Выберите пункт меню: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
            continue;
        }

        if (!Validator::isValidMenuChoice(choice, 2)) {
            std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                task1CalcTree1();
                break;
            case 2:
                task2CalcTree23();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}