#include "stl3alg6.h"
#include "utils.h"
#include "stlprint.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

static bool inputManual(std::vector<int>& V, std::list<int>& L) {
    int countV = 0;

    if (!readIntMultiple("Размер вектора (четное число): ", 2, 20, 2, countV)) {
        return false;
    }

    V.clear();

    for (int i = 0; i < countV; ++i) {
        std::cout << "Элемент вектора " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-1000, 1000, x)) {
            return false;
        }

        V.push_back(x);
    }

    int countL = 0;

    if (!readInt("Размер списка: ", 0, 20, countL)) {
        return false;
    }

    L.clear();

    for (int i = 0; i < countL; ++i) {
        std::cout << "Элемент списка " << (i + 1) << ": ";

        int x = 0;
        if (!readIntNoPrompt(-1000, 1000, x)) {
            return false;
        }

        L.push_back(x);
    }

    return true;
}

static bool inputRandom(std::vector<int>& V, std::list<int>& L) {
    initRandom();

    int countV = randomInt(2, 8) * 2;
    int countL = randomInt(3, 10);

    V.clear();
    L.clear();

    for (int i = 0; i < countV; ++i) {
        V.push_back(randomInt(0, 9));
    }

    for (int i = 0; i < countL; ++i) {
        L.push_back(randomInt(0, 9));
    }

    std::cout << "\nСлучайные данные:\n";

    std::cout << "Вектор: ";
    bool first = true;
    printRange(V.begin(), V.end(), first);
    std::cout << '\n';

    std::cout << "Список: ";
    first = true;
    printRange(L.begin(), L.end(), first);
    std::cout << '\n';

    return true;
}

static bool inputFile(std::vector<int>& V, std::list<int>& L) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    int countV = 0;
    if (!(in >> countV)) {
        std::cout << "Не удалось прочитать размер вектора.\n";
        return false;
    }

    if (countV < 2 || countV > 100000 || countV % 2 != 0) {
        std::cout << "Некорректный размер вектора.\n";
        return false;
    }

    V.clear();

    for (int i = 0; i < countV; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы вектора.\n";
            return false;
        }

        V.push_back(x);
    }

    int countL = 0;
    if (!(in >> countL)) {
        std::cout << "Не удалось прочитать размер списка.\n";
        return false;
    }

    if (countL < 0 || countL > 100000) {
        std::cout << "Некорректный размер списка.\n";
        return false;
    }

    L.clear();

    for (int i = 0; i < countL; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы списка.\n";
            return false;
        }

        L.push_back(x);
    }

    return true;
}

static bool duplicateLastMatching(std::vector<int>& V, std::list<int>& L) {
    if (L.empty() || V.empty()) {
        return false;
    }

    std::vector<int>::iterator half = V.begin() + V.size() / 2;

    std::list<int>::reverse_iterator rit =
        std::find_first_of(L.rbegin(), L.rend(), V.begin(), half);

    if (rit == L.rend()) {
        return false;
    }

    L.insert(rit.base(), *rit);
    return true;
}

void runSTL3Alg6(int mode) {
    std::vector<int> V;
    std::list<int> L;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(V, L);
    } else if (mode == 2) {
        ok = inputRandom(V, L);
    } else if (mode == 3) {
        ok = inputFile(V, L);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nИсходный вектор: ";
    bool first = true;
    printRange(V.begin(), V.end(), first);
    std::cout << '\n';

    std::cout << "Исходный список: ";
    first = true;
    printRange(L.begin(), L.end(), first);
    std::cout << '\n';

    bool changed = duplicateLastMatching(V, L);

    if (!changed) {
        std::cout << "Подходящий элемент не найден. Список не изменен.\n";
    }

    std::cout << "Полученный список: ";
    first = true;
    printRange(L.begin(), L.end(), first);
    std::cout << '\n';
}