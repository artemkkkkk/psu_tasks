#include "fun_tasks.h"
#include <iostream>
#include <random>
#include <cmath>
#include <ctime>

void solveCoinToss() {
    std::cout << "[Задача 3] Моделирование 20 бросков монеты:\n";
    std::mt19937 gen(static_cast<unsigned>(std::time(0)));
    std::uniform_int_distribution<> dis(0, 1);

    int heads = 0, tails = 0;
    for (int i = 0; i < 20; ++i) {
        bool isHead = dis(gen);
        if (isHead) {
            std::cout << "Орёл ";
            ++heads;
        } else {
            std::cout << "Решка ";
            ++tails;
        }
    }
    std::cout << "\nИтого: Орёл — " << heads << ", Решка — " << tails << "\n";
}

// Факториал без рекурсии и вложенных циклов
long long factorial(int n) {
    long long f = 1;
    for (int i = 2; i <= n; ++i) f *= i;
    return f;
}

void solveSinApproximation() {
    int n;
    double x;
    std::cout << "[Задача 6] Введите n (кол-во членов ряда) и x: ";
    std::cin >> n >> x;

    if (n <= 0) {
        std::cout << "n должно быть натуральным\n";
        return;
    }

    double term = x; // первый член: x
    double sum = term;
    // Генерируем следующие члены: x^(2k+1) / (2k+1)! с чередующимся знаком
    for (int k = 1; k < n; ++k) {
        // Обновляем term: умножаем на -x^2 / ((2k)*(2k+1))
        term *= -x * x / ( (2 * k) * (2 * k + 1) );
        sum += term;
    }

    double realSin = std::sin(x);
    std::cout << "Приближение sin(" << x << ") по " << n << " членам: " << sum << "\n";
    std::cout << "Точное значение sin(" << x << "): " << realSin << "\n";
}