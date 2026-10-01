#include "listwork43.h"
#include "doublylist.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(DoublyList& list) {
    int count = 0;

    if (!readInt("Количество элементов списка: ", 1, 50, count)) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";
        int x = 0;

        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        list.pushBack(x);
    }

    return true;
}

static bool inputRandom(DoublyList& list) {
    initRandom();

    int count = randomInt(4, 10);

    for (int i = 0; i < count; ++i) {
        list.pushBack(randomInt(-100, 100));
    }

    std::cout << "\nСлучайный список:\n";
    list.print();

    return true;
}

static bool inputFile(DoublyList& list) {
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

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы.\n";
            return false;
        }

        list.pushBack(x);
    }

    std::cout << "Загружено из файла: " << fileName << '\n';
    return true;
}

void runListWork43(int mode) {
    DoublyList list;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(list);
    } else if (mode == 2) {
        ok = inputRandom(list);
    } else if (mode == 3) {
        ok = inputFile(list);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nИсходный список:\n";
    list.print();

    TNode2* first = list.moveOddPositionsToEnd();

    std::cout << "Преобразованный список:\n";
    list.print();

    printPointer("Адрес первого элемента преобразованного списка: ", first);
}