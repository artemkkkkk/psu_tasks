#include <iostream>
#include "fractions.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    std::cout << "=== Задача 6: Работа с дробями (вариант 1) ===\n";
    std::cout << "Формат ввода: числитель знаменатель (для каждой дроби)\n";

    int n1, d1, n2, d2;
    std::cout << "Первая дробь: ";
    std::cin >> n1 >> d1;
    std::cout << "Вторая дробь: ";
    std::cin >> n2 >> d2;

    int sum_n, sum_d, mult_n, mult_d;
    Summ(n1, d1, n2, d2, sum_n, sum_d);
    Mult(n1, d1, n2, d2, mult_n, mult_d);

    std::cout << "\nРезультаты:\n";
    std::cout << "Сумма: ";
    PrintFraction(sum_n, sum_d);
    std::cout << "\nПроизведение: ";
    PrintFraction(mult_n, mult_d);
    std::cout << "\n\n";

    // Тесты
    /*
    Тест 1: 1/2 + 1/3 = 5/6
    Тест 2: 2/4 * 3/5 = (1/2)*(3/5) = 3/10
    Тест 3: 0/7 + 5/1 = 5
    Тест 4: -2/3 + 2/3 = 0
    */

    std::cout << "≽^•⩊•^≼ \n\n";
    std::cout << "Введите любой символ для завершения \n";
    std::cin >> n1;
    return 0;
}