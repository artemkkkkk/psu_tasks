#include "menu.h"
#include <iostream>
#include <limits>

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

std::string Menu::getExpressionInput() {
    std::string expression;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nВведите постфиксное выражение: ";
    std::getline(std::cin, expression);

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