#include "while_tasks.h"
#include <iostream>
#include <cmath>

void solveWhile17() {
    long long N;
    std::cout << "[While17] Введите целое число N (>0): ";
    std::cin >> N;
    if (N <= 0) {
        std::cout << "Число должно быть положительным.\n";
        return;
    }
    std::cout << "Цифры числа справа налево:\n";
    while (N > 0) {
        std::cout << N % 10 << " ";
        N /= 10;
    }
    std::cout << "\n";
}

void solveTheTwo17() {
    long long N;
    std::cout << "[TheTwo17] Введите натуральное число N (<1000000000): ";
    std::cin >> N;
    if (N <= 0 || N >= 1000000000) {
        std::cout << "Некорректное число.\n";
        return;
    }

    int maxDigit = -1;
    int bestPos = -1;
    int pos = 1;

    while (N > 0) {
        int digit = N % 10;
        if (digit > maxDigit) {
            maxDigit = digit;
            bestPos = pos;
        }
        N /= 10;
        ++pos;
    }

    std::cout << "Максимальная цифра: " << maxDigit << "\n";
    std::cout << "Её позиция (справа налево): " << bestPos << "\n";
}