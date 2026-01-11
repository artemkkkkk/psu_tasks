#include "fractions.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

int Nod(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void Sokr(int& num, int& den) {
    if (den == 0)
        throw std::invalid_argument("Знаменатель не может быть нулём");
    if (den < 0) {
        num = -num;
        den = -den;
    }
    int g = Nod(num, den);
    if (g != 0) {
        num /= g;
        den /= g;
    }
}

void Summ(int n1, int d1, int n2, int d2, int& nr, int& dr) {
    nr = n1 * d2 + n2 * d1;
    dr = d1 * d2;
    Sokr(nr, dr);
}

void Mult(int n1, int d1, int n2, int d2, int& nr, int& dr) {
    nr = n1 * n2;
    dr = d1 * d2;
    Sokr(nr, dr);
}

void PrintFraction(int num, int den) {
    if (den == 1)
        std::cout << num;
    else if (den == -1)
        std::cout << -num;
    else
        std::cout << num << "/" << den;
}