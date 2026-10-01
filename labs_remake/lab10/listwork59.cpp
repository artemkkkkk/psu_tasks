#include "listwork59.h"
#include "list.h"
#include "utils.h"
#include "nodeio.h"
#include <iostream>
#include <fstream>

static bool inputManual(List& list, int& m, int& k) {
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

    if (!readInt("Вставляемое значение M: ", -10000, 10000, m)) {
        return false;
    }

    if (!readInt("Значение K: ", 1, 50, k)) {
        return false;
    }

    return true;
}

static bool inputRandom(List& list, int& m, int& k) {
    initRandom();

    int count = randomInt(3, 12);

    for (int i = 0; i < count; ++i) {
        list.pushBack(randomInt(-100, 100));
    }

    m = randomInt(-100, 100);
    k = randomInt(1, 5);

    std::cout << "\nСлучайные данные:\n";
    std::cout << "Исходный список: ";
    list.print();
    std::cout << "M = " << m << ", K = " << k << '\n';

    return true;
}

static bool inputFile(List& list, int& m, int& k) {
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
            std::cout << "Не удалось прочитать элементы списка.\n";
            return false;
        }

        list.pushBack(x);
    }

    if (!(in >> m)) {
        std::cout << "Не удалось прочитать значение M.\n";
        return false;
    }

    if (!(in >> k)) {
        std::cout << "Не удалось прочитать значение K.\n";
        return false;
    }

    if (k < 1) {
        std::cout << "Значение K должно быть положительным.\n";
        return false;
    }

    return true;
}

void runListWork59(int mode) {
    List list;
    int m = 0;
    int k = 1;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(list, m, k);
    } else if (mode == 2) {
        ok = inputRandom(list, m, k);
    } else if (mode == 3) {
        ok = inputFile(list, m, k);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nИсходный список: ";
    list.print();

    list.insertAfterEveryK(k, m);

    std::cout << "Список после вставки: ";
    list.print();

    TNode* p2 = list.lastNode();

    printNodePointer("Указатель на последний элемент полученного списка: ", p2);
    printNodeValue("Значение последнего элемента: ", p2);
}