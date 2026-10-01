#include "task1.h"
#include "point.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(int xs[3], int ys[3]) {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Точка " << (i + 1) << '\n';

        if (!readInt("X: ", -1000, 1000, xs[i])) {
            return false;
        }

        if (!readInt("Y: ", -1000, 1000, ys[i])) {
            return false;
        }
    }

    return true;
}

static bool inputRandom(int xs[3], int ys[3]) {
    initRandom();

    std::cout << "\nСлучайные точки:\n";

    for (int i = 0; i < 3; ++i) {
        xs[i] = randomInt(-100, 100);
        ys[i] = randomInt(-100, 100);

        std::cout << "Точка " << (i + 1) << ": {" << xs[i] << ";" << ys[i] << "}\n";
    }

    return true;
}

static bool inputFile(int xs[3], int ys[3]) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        if (!(in >> xs[i] >> ys[i])) {
            std::cout << "Не удалось прочитать координаты точки.\n";
            return false;
        }
    }

    return true;
}

void runTask1(int mode) {
    int xs[3];
    int ys[3];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(xs, ys);
    } else if (mode == 2) {
        ok = inputRandom(xs, ys);
    } else if (mode == 3) {
        ok = inputFile(xs, ys);
    }

    if (!ok) {
        return;
    }

    Point p1(xs[0], ys[0]);
    Point p2(xs[1], ys[1]);
    Point p3(xs[2], ys[2]);

    std::cout << "\nРезультат:\n";

    std::cout << "Точка 1: ";
    p1.print();

    std::cout << "Точка 2: ";
    p2.print();

    std::cout << "Точка 3: ";
    p3.print();
}