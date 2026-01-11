#include <iostream>
#include <vector>
#include "tasks1_5.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    int choice;
    do {
        std::cout << "\n=== Лабораторная №3: Задачи 1–5 (Вариант 1) ===\n";
        std::cout << "1. Proc27 — Проверка, является ли число степенью N\n";
        std::cout << "2. Proc15 — Левый циклический сдвиг трёх чисел\n";
        std::cout << "3. Proc43 — Приближение ln(1+x)\n";
        std::cout << "4. TheTri13 — Перевод из системы с основанием P в десятичную\n";
        std::cout << "5. Reccur16 — Рекурсивная сумма x + x^3 + ... (N членов)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите задачу: ";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    int N;
                    std::cout << "Введите основание N (>1): ";
                    std::cin >> N;
                    std::vector<int> arr(10);
                    std::cout << "Введите 10 положительных целых чисел:\n";
                    for (int i = 0; i < 10; ++i) std::cin >> arr[i];
                    int cnt = 0;
                    for (int k : arr)
                        if (IsPowerN(k, N)) ++cnt;
                    std::cout << "Количество степеней числа " << N << ": " << cnt << "\n";
                    break;
                }
                case 2: {
                    double A1, B1, C1, A2, B2, C2;
                    std::cout << "Введите A1 B1 C1: "; std::cin >> A1 >> B1 >> C1;
                    std::cout << "Введите A2 B2 C2: "; std::cin >> A2 >> B2 >> C2;
                    ShiftLeft3(A1, B1, C1);
                    ShiftLeft3(A2, B2, C2);
                    std::cout << "После сдвига:\n";
                    std::cout << "Набор 1: " << A1 << " " << B1 << " " << C1 << "\n";
                    std::cout << "Набор 2: " << A2 << " " << B2 << " " << C2 << "\n";
                    break;
                }
                case 3: {
                    double x;
                    std::cout << "Введите x (|x| < 1): ";
                    std::cin >> x;
                    std::vector<double> eps(6);
                    std::cout << "Введите 6 значений ε (>0):\n";
                    for (int i = 0; i < 6; ++i) std::cin >> eps[i];
                    for (double e : eps) {
                        std::cout << "ln(1+" << x << ") ≈ " << Ln1(x, e)
                                  << " (ε = " << e << ")\n";
                    }
                    break;
                }
                case 4: {
                    int X, P;
                    std::cout << "Введите число X в системе с основанием P: ";
                    std::cin >> X;
                    std::cout << "Введите основание P (2–9): ";
                    std::cin >> P;
                    int dec = FromBasePToDec(X, P);
                    std::cout << "Результат в десятичной системе: " << dec << "\n";
                    break;
                }
                case 5: {
                    double x;
                    int N;
                    std::cout << "Введите x: ";
                    std::cin >> x;
                    std::cout << "Введите N (<20): ";
                    std::cin >> N;
                    if (N < 1 || N >= 20) {
                        std::cout << "N должно быть натуральным и <20!\n";
                    } else {
                        double res = RecSumOddPowers(x, N);
                        std::cout << "Сумма = " << res << "\n";
                    }
                    break;
                }
                case 0:
                    std::cout << "Выход из программы.\n";
                    break;
                default:
                    std::cout << "Неверный выбор.\n";
            }
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка: " << ex.what() << "\n";
        }
    } while (choice != 0);

    return 0;
}