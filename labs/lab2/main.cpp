#include <iostream>
#include "while_tasks.h"
#include "series_tasks.h"
#include "fun_tasks.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    int task;
    do {
        std::cout << "\n=== Лабораторная работа №2 (Вариант 1) ===\n";
        std::cout << "1. While17 — вывод цифр числа справа налево\n";
        std::cout << "2. Series4 — сумма и произведение N чисел\n";
        std::cout << "3. Задача 3 — бросание монеты (20 раз)\n";
        std::cout << "4. TheTwo11 — сумма i^i\n";
        std::cout << "5. TheTwo17 — макс. цифра с наибольшим номером\n";
        std::cout << "6. Задача 6 — приближение sin(x) рядом Тейлора\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите задачу: ";
        std::cin >> task;

        switch (task) {
            case 1: solveWhile17(); break;
            case 2: solveSeries4(); break;
            case 3: solveCoinToss(); break;
            case 4: solveTheTwo11(); break;
            case 5: solveTheTwo17(); break;
            case 6: solveSinApproximation(); break;
            case 0: std::cout << "Выход...\n"; break;
            default: std::cout << "Неверный выбор.\n";
        }
    } while (task != 0);

    std::cout << "\n";
    std::cout << "≽^•⩊•^≼ \n\n";
    std::cout << "Введите любой символ для завершения \n";
    std::cin >> task;
    return 0;
}