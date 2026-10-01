#include "task5.h"
#include "line.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(int coords[4]) {
    std::cout << "Координаты линии:\n";

    if (!readInt("X начала: ", -1000, 1000, coords[0])) return false;
    if (!readInt("Y начала: ", -1000, 1000, coords[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, coords[2])) return false;
    if (!readInt("Y конца: ", -1000, 1000, coords[3])) return false;

    return true;
}

static bool inputRandom(int coords[4]) {
    initRandom();

    coords[0] = randomInt(-100, 100);
    coords[1] = randomInt(-100, 100);
    coords[2] = randomInt(-100, 100);
    coords[3] = randomInt(-100, 100);

    std::cout << "\nСлучайные координаты линии:\n";
    std::cout << "Начало: {" << coords[0] << ";" << coords[1] << "}\n";
    std::cout << "Конец: {" << coords[2] << ";" << coords[3] << "}\n";

    return true;
}

static bool inputFile(int coords[4]) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> coords[0] >> coords[1] >> coords[2] >> coords[3])) {
        std::cout << "Не удалось прочитать координаты линии.\n";
        return false;
    }

    return true;
}

void runTask5(int mode) {
    int coords[4];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(coords);
    } else if (mode == 2) {
        ok = inputRandom(coords);
    } else if (mode == 3) {
        ok = inputFile(coords);
    }

    if (!ok) {
        return;
    }

    Line line(coords[0], coords[1], coords[2], coords[3]);

    std::cout << "\nРезультат:\n";

    std::cout << "Линия: ";
    line.print();

    std::cout << "Длина линии: " << line.length() << '\n';
}