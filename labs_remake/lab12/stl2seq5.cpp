#include "stl2seq5.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>

static bool inputManual(std::list<int>& L) {
    int count = 0;

    if (!readIntMultiple("Количество элементов (кратное 3): ", 3, 60, 3, count)) {
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

    L = std::list<int>(temp.begin(), temp.end());
    return true;
}

static bool inputRandom(std::list<int>& L) {
    initRandom();

    int count = randomInt(2, 8) * 3;
    std::vector<int> temp;
    temp.reserve(count);

    for (int i = 0; i < count; ++i) {
        temp.push_back(randomInt(-100, 100));
    }

    L = std::list<int>(temp.begin(), temp.end());

    std::cout << "\nСлучайные данные:\n";
    bool first = true;
    printRange(L.begin(), L.end(), first);
    std::cout << '\n';

    return true;
}

static bool inputFile(std::list<int>& L) {
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

    if (count < 3 || count > 100000 || count % 3 != 0) {
        std::cout << "Некорректное количество элементов.\n";
        return false;
    }

    std::list<int> temp((std::istream_iterator<int>(in)), std::istream_iterator<int>());

    if (static_cast<int>(temp.size()) != count) {
        std::cout << "Файл содержит некорректное количество элементов.\n";
        return false;
    }

    L = temp;
    return true;
}

void runSTL2Seq5(int mode) {
    std::list<int> L;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(L);
    } else if (mode == 2) {
        ok = inputRandom(L);
    } else if (mode == 3) {
        ok = inputFile(L);
    }

    if (!ok) {
        return;
    }

    if (L.size() < 3 || L.size() % 3 != 0) {
        std::cout << "Количество элементов должно быть кратно 3.\n";
        return;
    }

    int third = static_cast<int>(L.size()) / 3;

    std::list<int>::iterator firstEnd = L.begin();
    std::advance(firstEnd, third);

    std::list<int>::iterator secondBegin = firstEnd;
    std::list<int>::iterator secondEnd = secondBegin;
    std::advance(secondEnd, third);

    std::list<int>::iterator thirdBegin = secondEnd;

    std::list<int> firstPart(L.begin(), firstEnd);
    std::list<int> secondPart(secondBegin, secondEnd);
    std::list<int> thirdPart(thirdBegin, L.end());

    std::cout << "\nРезультат:\n";

    bool first = true;
    printRange(firstPart.begin(), firstPart.end(), first);
    printRange(secondPart.rbegin(), secondPart.rend(), first);
    printRange(thirdPart.rbegin(), thirdPart.rend(), first);

    std::cout << '\n';
}