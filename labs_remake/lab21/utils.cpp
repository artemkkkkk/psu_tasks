#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

static bool isSpaceChar(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

bool readIntNoPrompt(int min, int max, int& value) {
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }

    while (true) {
        int x = 0;

        if (!(std::cin >> x)) {
            if (std::cin.eof()) {
                return false;
            }

            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            std::cout << "Ошибка ввода. Введите целое число.\n";
            continue;
        }

        std::cin.ignore(1000000, '\n');

        if (x < min || x > max) {
            std::cout << "Значение должно быть в диапазоне от " << min << " до " << max << ".\n";
            continue;
        }

        value = x;
        return true;
    }
}

bool readInt(const char* prompt, int min, int max, int& value) {
    std::cout << prompt;
    return readIntNoPrompt(min, max, value);
}

bool readFileName(const char* prompt, char* buffer, int bufferSize) {
    if (!buffer || bufferSize <= 0) {
        return false;
    }

    while (true) {
        std::cout << prompt;

        if (!std::cin.getline(buffer, bufferSize)) {
            if (std::cin.eof()) {
                return false;
            }

            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            std::cout << "Ошибка ввода имени файла.\n";
            continue;
        }

        char* s = buffer;

        while (*s && isSpaceChar(*s)) {
            ++s;
        }

        if (*s == '\0') {
            std::cout << "Имя файла не может быть пустым.\n";
            continue;
        }

        return true;
    }
}

void initRandom() {
    static bool initialized = false;
    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(0)));
        initialized = true;
    }
}

int randomInt(int min, int max) {
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }

    if (min == max) {
        return min;
    }

    return min + std::rand() % (max - min + 1);
}