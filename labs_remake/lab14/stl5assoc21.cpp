#include "stl5assoc21.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>

static void printIntVector(const std::vector<int>& V) {
    bool first = true;

    for (std::vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) {
        if (!first) {
            std::cout << ' ';
        }

        std::cout << *it;
        first = false;
    }

    std::cout << '\n';
}

static bool inputManual(std::vector<int>& V) {
    int count = 0;

    if (!readInt("Количество элементов: ", 1, 30, count)) {
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

    int count = randomInt(6, 12);

    V.clear();

    for (int i = 0; i < count; ++i) {
        V.push_back(randomInt(-100, 100));
    }

    std::cout << "\nСлучайные данные:\n";
    printIntVector(V);

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

    if (count < 1 || count > 100000) {
        std::cout << "Некорректное количество элементов.\n";
        return false;
    }

    V.clear();

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы.\n";
            return false;
        }

        V.push_back(x);
    }

    return true;
}

static void buildMultimap(const std::vector<int>& V, std::multimap<int, int>& M) {
    M.clear();

    for (std::vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) {
        int key = std::abs(*it) % 10;
        M.insert(M.upper_bound(key), std::make_pair(key, *it));
    }
}

void runSTL5Assoc21(int mode) {
    std::vector<int> V;
    std::multimap<int, int> M;

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

    if (V.empty()) {
        std::cout << "Вектор пуст.\n";
        return;
    }

    std::cout << "\nИсходный вектор: ";
    printIntVector(V);

    buildMultimap(V, M);

    std::cout << "Полученное мультиотображение (ключ, элемент):\n";

    for (std::multimap<int, int>::const_iterator it = M.begin(); it != M.end(); ++it) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
}