#include "stl2seq8.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

static bool inputManual(std::vector<int>& V) {
    int count = 0;

    if (!readIntMultiple("Количество элементов (четное): ", 2, 60, 2, count)) {
        return false;
    }

    std::vector<int> temp;
    temp.reserve(count);

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        temp.push_back(x);
    }

    V = std::vector<int>(temp.begin(), temp.end());
    return true;
}

static bool inputRandom(std::vector<int>& V) {
    initRandom();

    int count = randomInt(2, 10) * 2;
    std::vector<int> temp;
    temp.reserve(count);

    for (int i = 0; i < count; ++i) {
        temp.push_back(randomInt(-100, 100));
    }

    V = std::vector<int>(temp.begin(), temp.end());

    std::cout << "\nСлучайные данные:\n";
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

    if (count < 2 || count > 100000 || count % 2 != 0) {
        std::cout << "Некорректное количество элементов.\n";
        return false;
    }

    std::vector<int> temp((std::istream_iterator<int>(in)), std::istream_iterator<int>());

    if (static_cast<int>(temp.size()) != count) {
        std::cout << "Файл содержит некорректное количество элементов.\n";
        return false;
    }

    V = temp;
    return true;
}

void runSTL2Seq8(int mode) {
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

    if (V.size() < 2 || V.size() % 2 != 0) {
        std::cout << "Количество элементов должно быть четным.\n";
        return;
    }

    std::cout << "\nИсходный вектор:\n";
    bool first = true;
    printRange(V.begin(), V.end(), first);
    std::cout << '\n';

    V.insert(V.begin() + V.size() / 2, 5, 0);

    std::cout << "Полученный вектор:\n";
    first = true;
    printRange(V.begin(), V.end(), first);
    std::cout << '\n';
}