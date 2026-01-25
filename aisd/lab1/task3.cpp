#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    double a, b;
    std::cout << "Введите границы отрезка [a, b]: ";
    std::cin >> a >> b;

    if (a > b) {
        std::swap(a, b);
    }

    std::cout << "\nТаблица значений функции f(x) = x^2 + 2x - 20 на отрезке [" << a << ", " << b << "] с шагом 1:\n";
    std::cout << std::setw(10) << "x" << " | " << std::setw(10) << "f(x)" << std::endl;
    std::cout << "----------------------------------------\n";

    for (double x = a; x <= b; x += 1.0) {
        double fx = x * x + 2 * x - 20;
        std::cout << std::setw(10) << x << " | " << std::setw(10) << fx << std::endl;
    }

    std::cout << "\nГрафик по точкам (пример):\n";
    for (double x = a; x <= b; x += 1.0) {
        double fx = x * x + 2 * x - 20;
        std::cout << "(" << x << ", " << fx << ") ";
    }
    std::cout << std::endl;

    return 0;
}