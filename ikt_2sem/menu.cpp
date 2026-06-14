#include "menu.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <vector>

void Menu::displayMainMenu() {
    std::cout << "\n========================================\n";
    std::cout << "  КОНВЕРТЕР ПОСТФИКСНЫХ ВЫРАЖЕНИЙ\n";
    std::cout << "========================================\n";
    std::cout << "1. Преобразовать выражение\n";
    std::cout << "2. Примеры использования\n";
    std::cout << "3. Справка\n";
    std::cout << "0. Выход\n";
    std::cout << "========================================\n";
    std::cout << "Выберите пункт меню: ";
}

void Menu::displayInputMenu() {
    std::cout << "\n========================================\n";
    std::cout << "  ВЫБОР СПОСОБА ВВОДА\n";
    std::cout << "========================================\n";
    std::cout << "1. Ввод из консоли\n";
    std::cout << "2. Ввод из файла\n";
    std::cout << "3. Случайное выражение\n";
    std::cout << "0. Назад в главное меню\n";
    std::cout << "========================================\n";
    std::cout << "Выберите способ ввода: ";
}

void Menu::displayInfo() {
    std::cout << "\n=== Примеры постфиксных выражений ===\n";
    std::cout << "Инфиксная форма: a + b\n";
    std::cout << "Постфиксная форма: ab+\n\n";
    
    std::cout << "Инфиксная форма: a * b + c\n";
    std::cout << "Постфиксная форма: ab*c+\n\n";
    
    std::cout << "Инфиксная форма: (a + b) * c\n";
    std::cout << "Постфиксная форма: ab+c*\n\n";
    
    std::cout << "Инфиксная форма: a + b / c * d * e - a\n";
    std::cout << "Постфиксная форма: abc/d*e*+a-\n";
}

std::string Menu::getExpressionFromConsole() {
    std::string expression;
    
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\nВведите постфиксное выражение: ";
    std::getline(std::cin, expression);
    
    return expression;
}

std::string Menu::getExpressionFromFile() {
    std::string filename;
    std::string expression;
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\nВведите имя файла: ";
    std::getline(std::cin, filename);
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::getline(file, expression);
    file.close();
    
    if (expression.empty()) {
        throw std::runtime_error("Файл пуст или не содержит выражения");
    }
    
    return expression;
}

std::string Menu::generateRandomExpression() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> operandCountDist(3, 8);
    std::uniform_int_distribution<> operandDist(0, 25);
    std::uniform_int_distribution<> operatorDist(0, 3);
    
    int operandCount = operandCountDist(gen);
    std::vector<char> operands = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                                   'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    std::vector<char> operators = {'+', '-', '*', '/'};
    
    std::string expression;
    std::vector<char> stack;
    
    for (int i = 0; i < operandCount; ++i) {
        expression += operands[operandDist(gen)];
        stack.push_back('O');
        
        while (stack.size() >= 2 && (std::uniform_real_distribution<>(0, 1)(gen) < 0.4 || i == operandCount - 1)) {
            expression += operators[operatorDist(gen)];
            stack.pop_back();
            stack.pop_back();
            stack.push_back('R');
        }
    }
    
    while (stack.size() > 1) {
        expression += operators[operatorDist(gen)];
        stack.pop_back();
        stack.pop_back();
        stack.push_back('R');
    }
    
    return expression;
}

bool Menu::askContinue() {
    char choice;
    std::cout << "\nПродолжить работу? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return (choice == 'y' || choice == 'Y');
}

void Menu::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Menu::pause() {
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}