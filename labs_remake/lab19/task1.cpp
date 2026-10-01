#include "task1.h"
#include "utils.h"
#include "hamming.h"
#include <iostream>
#include <fstream>
#include <cstring>

static bool validBits(const char* s) {
    if (!s[0]) {
        return false;
    }

    for (int i = 0; s[i]; ++i) {
        if (s[i] != '0' && s[i] != '1') {
            return false;
        }
    }

    return true;
}

static bool inputManual(char* msg, int size) {
    std::cout << "Сообщение варианта: 1011110111111 (можно ввести своё).\n";

    if (!readNonEmptyString("Введите сообщение двоичной строкой: ", msg, size)) {
        return false;
    }

    if (!validBits(msg)) {
        std::cout << "Сообщение должно содержать только символы 0 и 1.\n";
        return false;
    }

    return true;
}

static bool inputRandom(char* msg, int size) {
    initRandom();

    int len = 13;

    if (len > size - 1) {
        len = size - 1;
    }

    for (int i = 0; i < len; ++i) {
        msg[i] = static_cast<char>('0' + randomInt(0, 1));
    }

    msg[len] = '\0';

    std::cout << "\nСлучайное сообщение: " << msg << '\n';
    return true;
}

static bool inputFile(char* msg, int size) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!in.getline(msg, size)) {
        std::cout << "Не удалось прочитать сообщение.\n";
        return false;
    }

    trimString(msg);

    if (!validBits(msg)) {
        std::cout << "Сообщение должно содержать только символы 0 и 1.\n";
        return false;
    }

    return true;
}

void runTask1(int mode) {
    char msg[128];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(msg, 128);
    } else if (mode == 2) {
        ok = inputRandom(msg, 128);
    } else if (mode == 3) {
        ok = inputFile(msg, 128);
    }

    if (!ok) {
        return;
    }

    int k = static_cast<int>(std::strlen(msg));
    int r = hammingParityBits(k);
    int n = k + r;

    int* code = new int[n + 1];
    int* received = new int[n + 1];

    std::cout << "\nИсходное сообщение: " << msg << '\n';
    std::cout << "Информационных бит k = " << k << ", контрольных бит r = " << r
              << ", всего n = " << n << "\n\n";

    std::cout << "Построение кода:\n";
    hammingEncodeWithSteps(msg, code, n, std::cout);

    std::cout << "\nКод Хемминга:\n";
    hammingPrintCode(code, n, std::cout);

    int errPos = 0;

    if (!readInt("Позиция искажения (1 - максимум, 0 - без ошибки, -1 - случайно): ", -1, n, errPos)) {
        delete[] code;
        delete[] received;
        return;
    }

    if (errPos == -1) {
        initRandom();
        errPos = randomInt(1, n);
    }

    for (int i = 1; i <= n; ++i) {
        received[i] = code[i];
    }

    if (errPos > 0) {
        received[errPos] ^= 1;
        std::cout << "\nИскажён бит в позиции " << errPos << ".\n";
    }

    std::cout << "Принятый код:\n";
    hammingPrintCode(received, n, std::cout);

    int syndrome = hammingSyndrome(received, n);

    if (syndrome == 0) {
        std::cout << "Синдром = 0: ошибок не обнаружено.\n";
    } else {
        std::cout << "Синдром = " << syndrome << ": ошибка в позиции " << syndrome
                  << ". Исправляем бит.\n";

        received[syndrome] ^= 1;

        std::cout << "Исправленный код:\n";
        hammingPrintCode(received, n, std::cout);
    }

    char restored[128];
    hammingExtract(received, n, restored);

    std::cout << "\nВосстановленное сообщение: " << restored << '\n';

    if (std::strcmp(restored, msg) == 0) {
        std::cout << "Сообщение восстановлено верно.\n";
    } else {
        std::cout << "Сообщение не совпадает с исходным!\n";
    }

    delete[] code;
    delete[] received;
}