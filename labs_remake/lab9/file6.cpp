#include "file6.h"
#include "utils.h"
#include "binaryio.h"
#include <iostream>
#include <fstream>
#include <new>

static bool prepareManual(int*& data, int& count, int& K) {
    if (!readInt("Количество элементов в файле: ", 0, 100, count)) {
        return false;
    }

    int allocateSize = count > 0 ? count : 1;
    data = new (std::nothrow) int[allocateSize];

    if (!data) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";
        if (!readIntNoPrompt(0, 100000, data[i])) {
            delete[] data;
            data = 0;
            return false;
        }
    }

    if (!readInt("Номер элемента K: ", 1, 1000, K)) {
        delete[] data;
        data = 0;
        return false;
    }

    if (!writeIntArray("file6_input.bin", data, count)) {
        delete[] data;
        data = 0;
        return false;
    }

    std::cout << "Создан файл file6_input.bin\n";
    return true;
}

static bool prepareRandom(int*& data, int& count, int& K) {
    initRandom();

    count = randomInt(5, 15);
    data = new (std::nothrow) int[count];

    if (!data) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        data[i] = randomInt(0, 1000);
    }

    K = randomInt(1, count + 3);

    if (!writeIntArray("file6_input.bin", data, count)) {
        delete[] data;
        data = 0;
        return false;
    }

    std::cout << "\nСлучайные данные:\n";
    std::cout << "Файл: file6_input.bin\n";
    std::cout << "Элементы: ";

    for (int i = 0; i < count; ++i) {
        std::cout << data[i] << ' ';
    }

    std::cout << '\n';
    std::cout << "K = " << K << '\n';

    return true;
}

static bool prepareFromFile(char* fileName, int& K) {
    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    if (!readInt("Номер элемента K: ", 1, 1000000, K)) {
        return false;
    }

    return true;
}

static void printFile6Result(int result) {
    std::ofstream out("output_file6.txt");

    std::cout << "\nРезультат: " << result << '\n';

    if (out) {
        out << result << '\n';
    }
}

void runFile6(int mode) {
    int* data = 0;
    int count = 0;
    int K = 0;
    char fileName[256];

    bool ok = false;

    if (mode == 1) {
        ok = prepareManual(data, count, K);
    } else if (mode == 2) {
        ok = prepareRandom(data, count, K);
    } else if (mode == 3) {
        ok = prepareFromFile(fileName, K);

        if (ok) {
            if (!readIntArray(fileName, data, count)) {
                std::cout << "Не удалось прочитать файл.\n";
                return;
            }
        }
    }

    if (!ok) {
        return;
    }

    int result = -1;

    if (K >= 1 && K <= count) {
        result = data[K - 1];
    }

    printFile6Result(result);

    delete[] data;
}