#include "series_tasks.h"
#include <iostream>
#include <cmath>

long long powerInt(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; ++i) res *= base;
    return res;
}

void solveSeries4() {
    int N;
    std::cout << "[Series4] Введите количество чисел N: ";
    std::cin >> N;
    if (N <= 0) {
        std::cout << "N должно быть > 0\n";
        return;
    }

    std::cout << "Введите числа: \n";

    double sum = 0.0, prod = 1.0;
    for (int i = 0; i < N; ++i) {
        double x;
        std::cin >> x;
        sum += x;
        prod *= x;
    }

    std::cout << "Сумма: " << sum << "\n";
    std::cout << "Произведение: " << prod << "\n";
}

void solveTheTwo11() {
    int n;
    std::cout << "[TheTwo11] Введите натуральное число n: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "n должно быть натуральным\n";
        return;
    }

    double total = 0.0;
    for (int i = 1; i <= n; ++i) {
        total += static_cast<double>(powerInt(i, i));
    }

    std::cout << "Результат: " << total << "\n";
}