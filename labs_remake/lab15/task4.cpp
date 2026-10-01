#include "task4.h"
#include "point.h"
#include "line.h"
#include "dependentline.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(int pointCoords[6], int line1Coords[4], int line2Coords[3]) {
    std::cout << "Координаты трех точек:\n";

    for (int i = 0; i < 3; ++i) {
        std::cout << "Точка " << (i + 1) << '\n';

        if (!readInt("X: ", -1000, 1000, pointCoords[i * 2])) {
            return false;
        }

        if (!readInt("Y: ", -1000, 1000, pointCoords[i * 2 + 1])) {
            return false;
        }
    }

    std::cout << "Линия 1:\n";

    if (!readInt("X начала: ", -1000, 1000, line1Coords[0])) return false;
    if (!readInt("Y начала: ", -1000, 1000, line1Coords[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, line1Coords[2])) return false;
    if (!readInt("Y конца: ", -1000, 1000, line1Coords[3])) return false;

    std::cout << "Линия 2 (горизонтальная):\n";

    if (!readInt("Y: ", -1000, 1000, line2Coords[0])) return false;
    if (!readInt("X начала: ", -1000, 1000, line2Coords[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, line2Coords[2])) return false;

    return true;
}

static bool inputRandom(int pointCoords[6], int line1Coords[4], int line2Coords[3]) {
    initRandom();

    for (int i = 0; i < 6; ++i) {
        pointCoords[i] = randomInt(-100, 100);
    }

    line1Coords[0] = randomInt(-50, 50);
    line1Coords[1] = randomInt(-50, 50);
    line1Coords[2] = randomInt(-50, 50);
    line1Coords[3] = randomInt(-50, 50);

    line2Coords[0] = randomInt(-50, 50);
    line2Coords[1] = randomInt(-80, -20);
    line2Coords[2] = randomInt(20, 80);

    std::cout << "\nСлучайные данные сгенерированы.\n";
    return true;
}

static bool inputFile(int pointCoords[6], int line1Coords[4], int line2Coords[3]) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    for (int i = 0; i < 6; ++i) {
        if (!(in >> pointCoords[i])) {
            std::cout << "Не удалось прочитать координаты точек.\n";
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (!(in >> line1Coords[i])) {
            std::cout << "Не удалось прочитать координаты линии 1.\n";
            return false;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (!(in >> line2Coords[i])) {
            std::cout << "Не удалось прочитать координаты линии 2.\n";
            return false;
        }
    }

    return true;
}

void runTask4(int mode) {
    int pointCoords[6];
    int line1Coords[4];
    int line2Coords[3];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(pointCoords, line1Coords, line2Coords);
    } else if (mode == 2) {
        ok = inputRandom(pointCoords, line1Coords, line2Coords);
    } else if (mode == 3) {
        ok = inputFile(pointCoords, line1Coords, line2Coords);
    }

    if (!ok) {
        return;
    }

    Point p1(pointCoords[0], pointCoords[1]);
    Point p2(pointCoords[2], pointCoords[3]);
    Point p3(pointCoords[4], pointCoords[5]);

    std::cout << "\nЗадача 4.1. Точки, созданные с указанием координат:\n";

    std::cout << "Точка 1: ";
    p1.print();

    std::cout << "Точка 2: ";
    p2.print();

    std::cout << "Точка 3: ";
    p3.print();

    Point line1Start(line1Coords[0], line1Coords[1]);
    Point line1End(line1Coords[2], line1Coords[3]);

    Line line1(line1Start, line1End);
    Line line2(line2Coords[1], line2Coords[0], line2Coords[2], line2Coords[0]);
    DependentLine line3(&line1, &line2);

    std::cout << "\nЗадача 4.2. Линии:\n";

    std::cout << "Линия 1: ";
    line1.print();

    std::cout << "Линия 2: ";
    line2.print();

    std::cout << "Линия 3: ";
    line3.print();
}