#include <iostream>
#include <limits>
#include <stdexcept>
#include "menu.h"
#include "expression_converter.h"
#include "exceptions.h"

#ifdef _WIN32
#include <windows.h>
#endif


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Menu menu;
    ExpressionConverter converter;
    bool running = true;

    while (running) {
        try {
            menu.displayMainMenu();

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string expression = menu.getExpressionInput();

                    if (expression.empty()) {
                        std::cout << "Ошибка: выражение не может быть пустым!\n";
                        break;
                    }

                    try {
                        auto instructions = converter.convertToInstructions(expression);
                        converter.printInstructions(instructions);
                    } catch (const ValidationException& e) {
                        std::cerr << "Ошибка валидации: " << e.what() << "\n";
                    } catch (const ConversionException& e) {
                        std::cerr << "Ошибка преобразования: " << e.what() << "\n";
                    }
                    break;
                }

                case 2: {
                    menu.displayInfo();

                    std::cout << "\n=== Демонстрация преобразования ===\n";
                    std::string demoExpr = "ABC*+DE-/";
                    std::cout << "Выражение: " << demoExpr << "\n";

                    try {
                        auto instructions = converter.convertToInstructions(demoExpr);
                        converter.printInstructions(instructions);
                    } catch (const std::exception& e) {
                        std::cerr << "Ошибка: " << e.what() << "\n";
                    }
                    break;
                }

                case 3: {
                    std::cout << "\n=== Справка ===\n";
                    std::cout << "Программа преобразует постфиксные выражения\n";
                    std::cout << "в последовательность инструкций для АВМ.\n\n";
                    std::cout << "Поддерживаемые операции:\n";
                    std::cout << "  + сложение (AD)\n";
                    std::cout << "  - вычитание (SB)\n";
                    std::cout << "  * умножение (ML)\n";
                    std::cout << "  / деление (DV)\n\n";
                    std::cout << "Операнды: буквы латинского алфавита или цифры\n";
                    break;
                }

                case 0: {
                    std::cout << "\nЗавершение работы программы...\n";
                    running = false;
                    break;
                }

                default: {
                    std::cout << "Неверный выбор! Попробуйте снова.\n";
                }
            }

            if (running && choice != 0) {
                menu.pause();
            }

        } catch (const std::exception& e) {
            std::cerr << "Неожиданная ошибка: " << e.what() << "\n";
            menu.pause();
        }
    }

    return 0;
}