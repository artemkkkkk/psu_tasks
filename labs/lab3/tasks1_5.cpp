#include "tasks1_5.h"
#include <cmath>
#include <stdexcept>

// Задача 1
bool IsPowerN(int K, int N) {
    if (K <= 0 || N <= 1) return false;
    while (K % N == 0) {
        K /= N;
    }
    return K == 1;
}

// Задача 2
void ShiftLeft3(double& A, double& B, double& C) {
    double temp = A;
    A = B;
    B = C;
    C = temp;
}

// Задача 3
double Ln1(double x, double eps) {
    if (std::abs(x) >= 1.0 || eps <= 0)
        throw std::invalid_argument("Некорректные параметры для Ln1");
    double term = x;
    double sum = term;
    int n = 1;
    while (std::abs(term) > eps) {
        term *= -x * static_cast<double>(n) / static_cast<double>(n + 1);
        sum += term;
        ++n;
    }
    return sum;
}

// Задача 4
int FromBasePToDec(int numInBaseP, int base) {
    if (base < 2 || base > 9)
        throw std::invalid_argument("Основание должно быть от 2 до 9");
    int result = 0;
    int power = 1;
    while (numInBaseP > 0) {
        int digit = numInBaseP % 10;
        if (digit >= base)
            throw std::invalid_argument("Недопустимая цифра в числе");
        result += digit * power;
        power *= base;
        numInBaseP /= 10;
    }
    return result;
}

// Вспомогательная рекурсивная функция для возведения в степень
double PowerRec(double x, int p) {
    if (p == 0) return 1.0;
    return x * PowerRec(x, p - 1);
}

// Задача 5: S = x + x^3 + x^5 + ... (N слагаемых)
double RecSumOddPowers(double x, int n) {
    if (n <= 0) return 0.0;
    int exp = 2 * n - 1; // нечётные степени: 1,3,5,...
    return RecSumOddPowers(x, n - 1) + PowerRec(x, exp);
}