#include "listwork1.h"
#include "list.h"
#include "utils.h"
#include "nodeio.h"
#include <iostream>
#include <fstream>

static bool inputManual(List& list) {
    int count = 0;

    if (!readInt("Количество элементов списка: ", 2, 50, count)) {
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

static bool inputRandom(List& list) {
    initRandom();

    int count = randomInt(3, 10);

    for (int i = 0; i < count; ++i) {
        list.pushBack(randomInt(-100, 100));
    }

    std::cout << "\nСлучайный список: ";
    list.print();

    return true;
}

static bool inputFile(List& list) {
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

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы списка.\n";
            return false;
        }

        list.pushBack(x);
    }

    return true;
}

void runListWork1(int mode) {
    List list;

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

    if (list.count() < 2) {
        std::cout << "В списке должно быть не менее двух элементов.\n";
        return;
    }

    std::cout << "\nИсходный список: ";
    list.print();

    TNode* p2 = list.at(2);

    printNodePointer("Указатель на второй элемент списка: ", p2);
    printNodeValue("Значение второго элемента: ", p2);
}