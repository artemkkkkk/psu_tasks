#include "dynamic3.h"
#include "stack.h"
#include "utils.h"
#include "nodeio.h"
#include <iostream>
#include <fstream>

static bool inputManual(Stack& stack, int& d) {
    int count = 0;

    std::cout << "Элементы добавляются в стек в порядке ввода. Последний введенный элемент станет вершиной.\n";

    if (!readInt("Количество элементов стека: ", 1, 50, count)) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";
        int x = 0;

        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        stack.push(x);
    }

    if (!readInt("Добавляемое число D: ", -10000, 10000, d)) {
        return false;
    }

    return true;
}

static bool inputRandom(Stack& stack, int& d) {
    initRandom();

    int count = randomInt(3, 8);

    for (int i = 0; i < count; ++i) {
        stack.push(randomInt(-100, 100));
    }

    d = randomInt(-100, 100);

    std::cout << "\nСлучайные данные:\n";
    std::cout << "Стек (от вершины к началу): ";
    stack.print();
    std::cout << "D = " << d << '\n';

    return true;
}

static bool inputFile(Stack& stack, int& d) {
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
            std::cout << "Не удалось прочитать элементы стека.\n";
            return false;
        }

        stack.push(x);
    }

    if (!(in >> d)) {
        std::cout << "Не удалось прочитать число D.\n";
        return false;
    }

    return true;
}

void runDynamic3(int mode) {
    Stack stack;
    int d = 0;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(stack, d);
    } else if (mode == 2) {
        ok = inputRandom(stack, d);
    } else if (mode == 3) {
        ok = inputFile(stack, d);
    }

    if (!ok) {
        return;
    }

    if (stack.isEmpty()) {
        std::cout << "Исходный стек пуст.\n";
        return;
    }

    std::cout << "\nИсходный стек (от вершины к началу): ";
    stack.print();

    TNode* p1 = stack.topNode();
    printNodePointer("Адрес P1 вершины исходного стека: ", p1);

    stack.push(d);

    TNode* p2 = stack.topNode();
    printNodePointer("Адрес P2 новой вершины стека: ", p2);

    std::cout << "Стек после добавления (от вершины к началу): ";
    stack.print();
}