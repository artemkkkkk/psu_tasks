#include "task3.h"
#include "student.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool readNonEmptyLine(std::ifstream& in, char* buffer, int bufferSize) {
    while (true) {
        if (!(in >> std::ws)) {
            return false;
        }

        if (!in.getline(buffer, bufferSize)) {
            return false;
        }

        trimString(buffer);

        if (buffer[0] != '\0') {
            return true;
        }
    }
}

static bool inputManual(
    char vasyaName[64],
    char petyaName[64],
    char andreyName[64],
    int grades[100],
    int& gradeCount
) {
    if (!readNonEmptyString("Имя первого студента: ", vasyaName, 64)) {
        return false;
    }

    if (!readInt("Количество оценок первого студента: ", 1, 100, gradeCount)) {
        return false;
    }

    std::cout << "Оценки первого студента:\n";

    for (int i = 0; i < gradeCount; ++i) {
        std::cout << "Оценка " << (i + 1) << ": ";

        if (!readIntNoPrompt(1, 5, grades[i])) {
            return false;
        }
    }

    if (!readNonEmptyString("Имя второго студента: ", petyaName, 64)) {
        return false;
    }

    if (!readNonEmptyString("Имя третьего студента: ", andreyName, 64)) {
        return false;
    }

    return true;
}

static bool inputRandom(
    char vasyaName[64],
    char petyaName[64],
    char andreyName[64],
    int grades[100],
    int& gradeCount
) {
    initRandom();

    copyString(vasyaName, 64, "Вася");
    copyString(petyaName, 64, "Петя");
    copyString(andreyName, 64, "Андрей");

    gradeCount = randomInt(3, 5);

    std::cout << "\nСлучайные оценки студента " << vasyaName << ": ";

    for (int i = 0; i < gradeCount; ++i) {
        grades[i] = randomInt(2, 5);
        std::cout << grades[i] << ' ';
    }

    std::cout << '\n';
    return true;
}

static bool inputFile(
    char vasyaName[64],
    char petyaName[64],
    char andreyName[64],
    int grades[100],
    int& gradeCount
) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!readNonEmptyLine(in, vasyaName, 64)) {
        std::cout << "Не удалось прочитать имя первого студента.\n";
        return false;
    }

    if (!(in >> gradeCount)) {
        std::cout << "Не удалось прочитать количество оценок.\n";
        return false;
    }

    if (gradeCount < 1 || gradeCount > 100) {
        std::cout << "Некорректное количество оценок.\n";
        return false;
    }

    for (int i = 0; i < gradeCount; ++i) {
        if (!(in >> grades[i])) {
            std::cout << "Не удалось прочитать оценки.\n";
            return false;
        }
    }

    if (!readNonEmptyLine(in, petyaName, 64)) {
        std::cout << "Не удалось прочитать имя второго студента.\n";
        return false;
    }

    if (!readNonEmptyLine(in, andreyName, 64)) {
        std::cout << "Не удалось прочитать имя третьего студента.\n";
        return false;
    }

    return true;
}

void runTask3(int mode) {
    char vasyaName[64];
    char petyaName[64];
    char andreyName[64];
    int grades[100];
    int gradeCount = 0;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(vasyaName, petyaName, andreyName, grades, gradeCount);
    } else if (mode == 2) {
        ok = inputRandom(vasyaName, petyaName, andreyName, grades, gradeCount);
    } else if (mode == 3) {
        ok = inputFile(vasyaName, petyaName, andreyName, grades, gradeCount);
    }

    if (!ok) {
        return;
    }

    Student vasya(vasyaName, grades, gradeCount);
    Student petya = vasya;

    if (petya.getCount() > 0) {
        petya.setGrade(0, 5);
    }

    std::cout << "\nРезультат:\n";

    std::cout << "Вася: ";
    vasya.print();

    std::cout << "Петя: ";
    petya.print();

    std::cout << "Изменение первой оценки Пети не меняет оценки Васи, так как массив оценок был скопирован.\n";

    Student andrey = vasya;

    if (vasya.getCount() > 0) {
        vasya.setGrade(0, 2);
    }

    std::cout << "\nПосле изменения первой оценки Васи:\n";

    std::cout << "Вася: ";
    vasya.print();

    std::cout << "Андрей: ";
    andrey.print();

    std::cout << "Изменение оценок Васи не влияет на Андрея, так как Андрею была скопирована отдельная копия оценок.\n";
}