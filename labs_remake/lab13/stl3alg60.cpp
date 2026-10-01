#include "stl3alg60.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <numeric>
#include <iomanip>

static bool inputManual(std::list<int>& L) {
    int count = 0;

    if (!readInt("Количество элементов списка (не менее 2): ", 2, 20, count)) {
        return false;
    }

    L.clear();

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-1000, 1000, x)) {
            return false;
        }

        L.push_back(x);
    }

    return true;
}

static bool inputRandom(std::list<int>& L) {
    initRandom();

    int count = randomInt(2, 10);

    L.clear();

    for (int i = 0; i < count; ++i) {
        L.push_back(randomInt(-100, 100));
    }

    std::cout << "\nСлучайные данные:\n";

    std::cout << "Список: ";
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

    if (count < 2 || count > 100000) {
        std::cout << "Некорректное количество элементов.\n";
        return false;
    }

    L.clear();

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы списка.\n";
            return false;
        }

        L.push_back(x);
    }

    return true;
}

static void buildAverages(const std::list<int>& L, std::vector<double>& V) {
    V.clear();

    std::adjacent_difference(
        L.begin(),
        L.end(),
        std::back_inserter(V),
        [](int current, int previous) {
            return (current + previous) / 2.0;
        }
    );

    if (!V.empty()) {
        V.erase(V.begin());
    }
}

static void printDoubleVector(const std::vector<double>& V) {
    bool first = true;

    std::cout << std::fixed << std::setprecision(1);

    for (std::vector<double>::const_iterator it = V.begin(); it != V.end(); ++it) {
        if (!first) {
            std::cout << ' ';
        }

        std::cout << *it;
        first = false;
    }

    std::cout << '\n';
    std::cout.unsetf(std::ios_base::fixed);
}

void runSTL3Alg60(int mode) {
    std::list<int> L;
    std::vector<double> V;

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

    if (L.size() < 2) {
        std::cout << "Список должен содержать не менее двух элементов.\n";
        return;
    }

    std::cout << "\nИсходный список: ";
    bool first = true;
    printRange(L.begin(), L.end(), first);
    std::cout << '\n';

    buildAverages(L, V);

    std::cout << "Средние арифметические соседних элементов: ";
    printDoubleVector(V);
}