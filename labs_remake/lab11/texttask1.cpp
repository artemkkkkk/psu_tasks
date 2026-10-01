#include "texttask1.h"
#include "namering.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(NameRing& ring, int& words) {
    if (!readInt("Количество слов в считалке: ", 1, 1000, words)) {
        return false;
    }

    int count = 0;
    if (!readInt("Количество детей: ", 1, 100, count)) {
        return false;
    }

    char name[256];

    for (int i = 0; i < count; ++i) {
        std::cout << "Имя ребенка " << (i + 1) << ": ";

        if (!readNonEmptyString("", name, 256)) {
            return false;
        }

        ring.append(name);
    }

    return true;
}

static bool inputRandom(NameRing& ring, int& words) {
    initRandom();

    static const char* names[] = {
        "Аня",
        "Боря",
        "Вера",
        "Глеб",
        "Дима",
        "Ева",
        "Женя",
        "Зина",
        "Игорь",
        "Катя"
    };

    words = randomInt(2, 5);
    int count = randomInt(4, 7);

    for (int i = 0; i < count; ++i) {
        ring.append(names[i % 10]);
    }

    std::cout << "\nСлучайные данные:\n";
    std::cout << "Количество слов в считалке: " << words << '\n';
    std::cout << "Дети:\n";
    ring.print();

    return true;
}

static bool inputFile(NameRing& ring, int& words) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> words)) {
        std::cout << "Не удалось прочитать количество слов.\n";
        return false;
    }

    if (words <= 0) {
        std::cout << "Количество слов должно быть положительным.\n";
        return false;
    }

    in.ignore(1000000, '\n');

    char buffer[256];

    while (in.getline(buffer, 256)) {
        trimString(buffer);

        if (buffer[0] != '\0') {
            if (ring.count() >= 100) {
                std::cout << "Слишком много детей.\n";
                return false;
            }

            ring.append(buffer);
        }
    }

    if (ring.isEmpty()) {
        std::cout << "В файле нет имен детей.\n";
        return false;
    }

    std::cout << "Загружено из файла: " << fileName << '\n';
    return true;
}

void runTextTask1(int mode) {
    NameRing ring;
    int words = 1;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(ring, words);
    } else if (mode == 2) {
        ok = inputRandom(ring, words);
    } else if (mode == 3) {
        ok = inputFile(ring, words);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nИсходный круг:\n";
    ring.print();

    std::cout << "\nПорядок выбывания:\n";

    if (!ring.eliminateWithStep(words, "output_text1.txt")) {
        std::cout << "Не удалось создать выходной файл.\n";
        return;
    }

    std::cout << "Результат записан в файл output_text1.txt\n";
}