#include "homedyn13.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

static bool inputManual(int& K, int& N) {
    if (!readInt("Основание системы счисления K: ", 2, 10, K)) {
        return false;
    }

    int maxN = 25 - K;
    if (maxN > 19) {
        maxN = 19;
    }

    if (!readInt("Количество разрядов N: ", 2, maxN, N)) {
        return false;
    }

    return true;
}

static bool inputRandom(int& K, int& N) {
    initRandom();

    K = randomInt(2, 10);

    int maxN = 25 - K;
    if (maxN > 19) {
        maxN = 19;
    }

    N = randomInt(2, maxN);

    std::cout << "\nСлучайные данные:\n";
    std::cout << "K = " << K << ", N = " << N << '\n';

    return true;
}

static bool inputFile(int& K, int& N) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);

    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> K >> N)) {
        std::cout << "Не удалось прочитать данные.\n";
        return false;
    }

    if (K < 2 || K > 10 || N < 2 || N >= 20 || K + N >= 26) {
        std::cout << "Некорректные входные данные.\n";
        return false;
    }

    std::cout << "Загружено из файла: K = " << K << ", N = " << N << '\n';
    return true;
}

static long double solveHomeDyn13(int K, int N) {
    long double endNonZero = static_cast<long double>(K - 1);
    long double endZero = 0.0L;

    for (int i = 2; i <= N; ++i) {
        long double newNonZero = (endNonZero + endZero) * (K - 1);
        long double newZero = endNonZero;

        endNonZero = newNonZero;
        endZero = newZero;
    }

    return endNonZero + endZero;
}

static void printHomeDyn13Result(long double result) {
    std::ofstream out("output_homedyn13.txt");

    std::cout << "\nРезультат:\n";
    std::cout << "Количество чисел: ";
    std::cout << std::fixed << std::setprecision(0) << result << '\n';

    if (out) {
        out << std::fixed << std::setprecision(0) << result << '\n';
    }
}

void runHomeDyn13(int mode) {
    int K = 0;
    int N = 0;

    bool inputOk = false;

    if (mode == 1) {
        inputOk = inputManual(K, N);
    } else if (mode == 2) {
        inputOk = inputRandom(K, N);
    } else if (mode == 3) {
        inputOk = inputFile(K, N);
    }

    if (!inputOk) {
        return;
    }

    long double result = solveHomeDyn13(K, N);
    printHomeDyn13Result(result);
}