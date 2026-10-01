#include "listwork66.h"
#include "ring.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(Ring& ring) {
    int count = 0;

    if (!readInt("Количество элементов кольца: ", 1, 50, count)) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";
        int x = 0;

        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        ring.append(x);
    }

    return true;
}

static bool inputRandom(Ring& ring) {
    initRandom();

    int count = randomInt(5, 10);

    for (int i = 0; i < count; ++i) {
        ring.append(randomInt(1, 100));
    }

    std::cout << "\nСлучайное кольцо:\n";
    ring.print();

    return true;
}

static bool inputFile(Ring& ring) {
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

        ring.append(x);
    }

    std::cout << "Загружено кольцо из файла: " << fileName << '\n';
    return true;
}

void runListWork66(int mode) {
    Ring ring;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(ring);
    } else if (mode == 2) {
        ok = inputRandom(ring);
    } else if (mode == 3) {
        ok = inputFile(ring);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nИсходное кольцо:\n";
    ring.print();

    std::cout << "\nПорядок удаления с шагом 3:\n";

    if (!ring.eliminateWithStep(3, "output_listwork66.txt")) {
        std::cout << "Не удалось создать выходной файл.\n";
        return;
    }

    std::cout << "Результат записан в файл output_listwork66.txt\n";
}