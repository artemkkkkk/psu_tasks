#include "file29.h"
#include "utils.h"
#include "binaryio.h"
#include <iostream>
#include <fstream>
#include <new>

static bool prepareManual() {
    int count = 0;

    if (!readInt("Количество элементов (больше 50): ", 51, 80, count)) {
        return false;
    }

    int* data = new (std::nothrow) int[count];

    if (!data) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";
        if (!readIntNoPrompt(-100000, 100000, data[i])) {
            delete[] data;
            return false;
        }
    }

    if (!writeIntArray("file29_data.bin", data, count)) {
        delete[] data;
        return false;
    }

    delete[] data;
    std::cout << "Создан файл file29_data.bin\n";
    return true;
}

static bool prepareRandom() {
    initRandom();

    int count = randomInt(51, 70);
    int* data = new (std::nothrow) int[count];

    if (!data) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        data[i] = randomInt(-1000, 1000);
    }

    if (!writeIntArray("file29_data.bin", data, count)) {
        delete[] data;
        return false;
    }

    delete[] data;

    std::cout << "\nСлучайные данные:\n";
    std::cout << "Файл: file29_data.bin\n";
    std::cout << "Количество элементов: " << count << '\n';

    return true;
}

static void printFile29Result(bool ok, int initialCount, int finalCount) {
    std::ofstream out("output_file29.txt");

    std::cout << "\nРезультат:\n";

    if (!ok) {
        std::cout << "Не удалось обработать файл.\n";

        if (out) {
            out << "Error\n";
        }

        return;
    }

    std::cout << "Начальный размер файла: " << initialCount << '\n';
    std::cout << "Конечный размер файла: " << finalCount << '\n';

    if (initialCount <= 50) {
        std::cout << "Файл уже содержит не более 50 элементов.\n";
    } else {
        std::cout << "Файл уменьшен до 50 элементов.\n";
    }

    if (out) {
        out << initialCount << ' ' << finalCount << '\n';
    }
}

void runFile29(int mode) {
    char fileName[256];
    fileName[0] = '\0';

    bool ok = false;

    if (mode == 1) {
        ok = prepareManual();
        copyString(fileName, 256, "file29_data.bin");
    } else if (mode == 2) {
        ok = prepareRandom();
        copyString(fileName, 256, "file29_data.bin");
    } else if (mode == 3) {
        ok = readFileName("Введите имя файла: ", fileName, 256);
    }

    if (!ok) {
        return;
    }

    int initialCount = 0;
    int finalCount = 0;

    ok = truncateIntBinaryFile(fileName, 50, initialCount, finalCount);
    printFile29Result(ok, initialCount, finalCount);
}