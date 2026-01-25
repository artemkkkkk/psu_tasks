#include <iostream>
#include <cmath>

int main() {
    long long S;
    std::cout << "Введите сумму номеров прочитанных страниц: ";
    std::cin >> S;

    if (S <= 0) {
        std::cout << "Сумма должна быть положительной." << std::endl;
        return 1;
    }

    long long D = 1 + 8 * S;
    long long sqrtD = static_cast<long long>(std::sqrt(D));

    if (sqrtD * sqrtD != D) {
        std::cout << "Нет такого количества страниц: сумма не соответствует полной последовательности 1+2+...+n." << std::endl;
        return 1;
    }

    if ((sqrtD - 1) % 2 != 0) {
        std::cout << "Нет такого количества страниц: сумма не соответствует полной последовательности 1+2+...+n." << std::endl;
        return 1;
    }

    long long n = (sqrtD - 1) / 2;

    if (n <= 0) {
        std::cout << "Некорректная сумма." << std::endl;
        return 1;
    }

    if (n * (n + 1) / 2 != S) {
        std::cout << "Нет такого количества страниц: сумма не соответствует полной последовательности 1+2+...+n." << std::endl;
        return 1;
    }

    std::cout << "Последняя прочитанная страница: " << n << std::endl;

    return 0;
}