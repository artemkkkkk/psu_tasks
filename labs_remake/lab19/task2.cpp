#include "task2.h"
#include "utils.h"
#include "huffman.h"
#include <iostream>
#include <fstream>

static bool inputManual(char* text, int size) {
    std::cout << "Текст варианта: БОБРЫ БОДРЫ И ДОБРЫ (можно ввести свой).\n";
    return readNonEmptyString("Введите текст: ", text, size);
}

static bool inputRandom(char* text, int size) {
    initRandom();

    static const char* phrases[] = {
        "БОБРЫ БОДРЫ И ДОБРЫ",
        "УВИДИМ ВАДИМА И УДИВИМ",
        "ДЯТЕЛ ДУБ ДОЛБИЛ",
        "КОВАЛЬ КОВАЛ КОНЯ",
        "НАШ ПОЛКАН ПОПАЛ В КАПКАН"
    };

    copyString(text, size, phrases[randomInt(0, 4)]);

    std::cout << "\nСлучайный текст: " << text << '\n';
    return true;
}

static bool inputFile(char* text, int size) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!in.getline(text, size)) {
        std::cout << "Не удалось прочитать текст.\n";
        return false;
    }

    trimString(text);

    if (text[0] == '\0') {
        std::cout << "Файл пуст.\n";
        return false;
    }

    return true;
}

void runTask2(int mode) {
    char text[512];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(text, 512);
    } else if (mode == 2) {
        ok = inputRandom(text, 512);
    } else if (mode == 3) {
        ok = inputFile(text, 512);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nТекст: " << text << '\n';

    huffmanBuildAndReport(text, std::cout);
}