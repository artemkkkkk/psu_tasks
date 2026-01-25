#include <iostream>
#include <cmath>

double ln_series(double x, double term, int n, double eps) {
    if (std::abs(term) < eps) {
        return 0.0;
    }
    double next_term = -term * (x - 1) / (n + 1);
    return term + ln_series(x, next_term, n + 1, eps);
}

int main() {
    double eps;
    std::cout << "Введите точность eps: ";
    std::cin >> eps;

    std::cout << "Введите x: ";
    double x;
    std::cin >> x;

    if (x <= 0 || x > 2) {
        std::cout << "Значение x = " << x << " вне допустимого диапазона (0 < x <= 2)" << std::endl;
        return 0;
    }

    double first_term = x - 1;
    double result = ln_series(x, first_term, 1, eps);

    double true_value = std::log(x);
    double error = std::abs(result - true_value);

    std::cout << "\n--- Для x = " << x << " ---" << std::endl;
    std::cout << "Вычисленное значение ln(x): " << result << std::endl;
    std::cout << "Точное значение (std::log): " << true_value << std::endl;
    std::cout << "Погрешность: " << error << std::endl;

    return 0;
}