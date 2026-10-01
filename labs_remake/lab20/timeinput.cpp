#include "timeinput.h"
#include "utils.h"
#include <iostream>
#include <fstream>

bool inputTimeData(int mode, int& hours, int& minutes, unsigned& addMinutes) {
    if (mode == 1) {
        if (!readInt("Часы (0..23): ", 0, 23, hours)) {
            return false;
        }

        if (!readInt("Минуты (0..59): ", 0, 59, minutes)) {
            return false;
        }

        int am = 0;
        if (!readInt("Сколько минут добавить: ", 0, 1000000, am)) {
            return false;
        }

        addMinutes = static_cast<unsigned>(am);
        return true;
    }

    if (mode == 2) {
        initRandom();

        hours = randomInt(0, 23);
        minutes = randomInt(0, 59);
        addMinutes = static_cast<unsigned>(randomInt(1, 500));

        std::cout << "\nСлучайные данные: время " << hours << ":" << minutes
                  << ", добавить " << addMinutes << " минут\n";
        return true;
    }

    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    int am = 0;

    if (!(in >> hours >> minutes >> am)) {
        std::cout << "Не удалось прочитать данные из файла.\n";
        return false;
    }

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || am < 0) {
        std::cout << "Некорректные данные в файле.\n";
        return false;
    }

    addMinutes = static_cast<unsigned>(am);
    return true;
}