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

bool readYesNo(const char* prompt, bool& yes) {
    while (true) {
        std::cout << prompt;

        char buffer[16];

        if (!std::cin.getline(buffer, 16)) {
            if (std::cin.eof()) {
                return false;
            }

            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            continue;
        }

        trimString(buffer);

        char c = buffer[0];

        if (c == 'y' || c == 'Y' || c == 'д' || c == 'Д') {
            yes = true;
            return true;
        }

        if (c == 'n' || c == 'N' || c == 'н' || c == 'Н') {
            yes = false;
            return true;
        }

        std::cout << "Введите 'y' или 'n'.\n";
    }
}

bool readNonEmptyString(const char* prompt, char* buffer, int bufferSize) {
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
            std::cout << "Ошибка ввода строки.\n";
            continue;
        }

        trimString(buffer);

        if (buffer[0] != '\0') {
            return true;
        }

        std::cout << "Строка не может быть пустой.\n";
    }
}

bool readFileName(const char* prompt, char* buffer, int bufferSize) {
    return readNonEmptyString(prompt, buffer, bufferSize);
}

void copyString(char* dest, int bufferSize, const char* src) {
    if (!dest || bufferSize <= 0) {
        return;
    }

    if (!src) {
        dest[0] = '\0';
        return;
    }

    int i = 0;
    while (i < bufferSize - 1 && src[i]) {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
}

void trimString(char* s) {
    if (!s) {
        return;
    }

    int start = 0;
    while (s[start] && isSpaceChar(s[start])) {
        ++start;
    }

    if (!s[start]) {
        s[0] = '\0';
        return;
    }

    int end = start;
    while (s[end]) {
        ++end;
    }
    --end;

    while (end >= start && isSpaceChar(s[end])) {
        --end;
    }

    int j = 0;
    for (int i = start; i <= end; ++i) {
        s[j++] = s[i];
    }

    s[j] = '\0';
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