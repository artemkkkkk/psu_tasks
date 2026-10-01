#include "stl2seq34.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>

static bool inputManual(std::list<int>& L1, std::list<int>& L2) {
    int count = 0;

    if (!readInt("Размер каждого списка: ", 1, 50, count)) {
        return false;
    }

    std::vector<int> a;
    std::vector<int> b;

    a.reserve(count);
    b.reserve(count);

    std::cout << "Элементы первого списка:\n";

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        a.push_back(x);
    }

    std::cout << "Элементы второго списка:\n";

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        b.push_back(x);
    }

    L1 = std::list<int>(a.begin(), a.end());
    L2 = std::list<int>(b.begin(), b.end());

    return true;
}

static bool inputRandom(std::list<int>& L1, std::list<int>& L2) {
    initRandom();

    int count = randomInt(3, 8);

    std::vector<int> a;
    std::vector<int> b;

    a.reserve(count);
    b.reserve(count);

    for (int i = 0; i < count; ++i) {
        a.push_back(randomInt(1, 100));
    }

    for (int i = 0; i < count; ++i) {
        b.push_back(randomInt(100, 999));
    }

    L1 = std::list<int>(a.begin(), a.end());
    L2 = std::list<int>(b.begin(), b.end());

    std::cout << "\nСлучайные данные:\n";

    std::cout << "Первый список: ";
    bool first = true;
    printRange(L1.begin(), L1.end(), first);
    std::cout << '\n';

    std::cout << "Второй список: ";
    first = true;
    printRange(L2.begin(), L2.end(), first);
    std::cout << '\n';

    return true;
}

static bool inputFile(std::list<int>& L1, std::list<int>& L2) {
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
        std::cout << "Не удалось прочитать размер списков.\n";
        return false;
    }

    if (count < 1 || count > 100000) {
        std::cout << "Некорректный размер списков.\n";
        return false;
    }

    std::vector<int> data((std::istream_iterator<int>(in)), std::istream_iterator<int>());

    if (static_cast<int>(data.size()) != 2 * count) {
        std::cout << "Файл содержит некорректное количество элементов.\n";
        return false;
    }

    L1 = std::list<int>(data.begin(), data.begin() + count);
    L2 = std::list<int>(data.begin() + count, data.end());

    return true;
}

static void combineLists(std::list<int>& L1, std::list<int>& L2) {
    int count = static_cast<int>(L1.size());

    std::list<int>::iterator i1 = L1.begin();
    std::list<int>::iterator i2 = L2.begin();

    for (int i = 0; i < count; ++i) {
        L2.splice(i2, L1, i1++);
        ++i2;
    }
}

void runSTL2Seq34(int mode) {
    std::list<int> L1;
    std::list<int> L2;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(L1, L2);
    } else if (mode == 2) {
        ok = inputRandom(L1, L2);
    } else if (mode == 3) {
        ok = inputFile(L1, L2);
    }

    if (!ok) {
        return;
    }

    if (L1.size() != L2.size()) {
        std::cout << "Списки должны иметь одинаковый размер.\n";
        return;
    }

    std::cout << "\nПервый список:\n";
    bool first = true;
    printRange(L1.begin(), L1.end(), first);
    std::cout << '\n';

    std::cout << "Второй список:\n";
    first = true;
    printRange(L2.begin(), L2.end(), first);
    std::cout << '\n';

    combineLists(L1, L2);

    std::cout << "Полученный второй список:\n";
    first = true;
    printRange(L2.begin(), L2.end(), first);
    std::cout << '\n';
}