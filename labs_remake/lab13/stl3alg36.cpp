#include "stl3alg36.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

static bool readOddCount(const char* prompt, int min, int max, int& value) {
    while (true) {
        int x = 0;

        if (!readInt(prompt, min, max, x)) {
            return false;
        }

        if (x % 2 == 1) {
            value = x;
            return true;
        }

        std::cout << "Количество элементов должно быть нечетным.\n";
    }
}

static bool inputManual(std::vector<int>& V) {
    int count = 0;

    if (!readOddCount("Количество элементов (нечетное, не менее 3): ", 3, 21, count)) {
        return false;
    }

    V.clear();

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-1000, 1000, x)) {
            return false;
        }

        V.push_back(x);
    }

    return true;
}

static bool inputRandom(std::vector<int>& V) {
    initRandom();

    int count = randomInt(1, 10) * 2 + 1;

    V.clear();

    for (int i = 0; i < count; ++i) {
        V.push_back(randomInt(-100, 100));
    }

    std::cout << "\nСлучайные данные:\n";

    std::cout << "Вектор: ";
    bool first = true;
    printRange(V.begin(), V.end(), first);
    std::cout << '\n';

    return true;
}

static bool inputFile(std::vector<int>& V) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    int count = 0;
    if (!(in >> count)) {
        std::cout << "Не удалось прочитать количество элементов.\n";
        return false;
    }

    if (count < 3 || count > 100000 || count % 2 != 1) {
        std::cout << "Некорректное количество элементов.\n";
        return false;
    }

    V.clear();

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы вектора.\n";
            return false;
        }

        V.push_back(x);
    }

    return true;
}

static void findMiddleSorted(std::vector<int>& V, int& leftMiddle, int& middle, int& rightMiddle) {
    std::vector<int>::iterator mid = V.begin() + V.size() / 2;

    std::nth_element(V.begin(), mid, V.end());

    std::vector<int>::iterator leftMax = std::max_element(V.begin(), mid);
    std::vector<int>::iterator rightMin = std::min_element(mid + 1, V.end());

    leftMiddle = *leftMax;
    middle = *mid;
    rightMiddle = *rightMin;
}

void runSTL3Alg36(int mode) {
    std::vector<int> V;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(V);
    } else if (mode == 2) {
        ok = inputRandom(V);
    } else if (mode == 3) {
        ok = inputFile(V);
    }

    if (!ok) {
        return;
    }

    if (V.size() < 3 || V.size() % 2 != 1) {
        std::cout << "Вектор должен содержать нечетное количество элементов, не менее 3.\n";
        return;
    }

    std::cout << "\nИсходный вектор: ";
    bool first = true;
    printRange(V.begin(), V.end(), first);
    std::cout << '\n';

    int leftMiddle = 0;
    int middle = 0;
    int rightMiddle = 0;

    findMiddleSorted(V, leftMiddle, middle, rightMiddle);

    std::cout << "Три средних элемента после сортировки: ";
    std::cout << leftMiddle << ' ' << middle << ' ' << rightMiddle << '\n';
}