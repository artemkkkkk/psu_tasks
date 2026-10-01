#include "recur14.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static const int EXPRESSION_MAX = 256;

static bool isDigitChar(char ch) {
    return ch >= '0' && ch <= '9';
}

static bool isOperatorChar(char ch) {
    return ch == '+' || ch == '-';
}

static int recursiveLength(const char* s) {
    if (!s || *s == '\0') {
        return 0;
    }

    return 1 + recursiveLength(s + 1);
}

static bool isValidRec(const char* s, int pos) {
    if (pos < 0) {
        return false;
    }

    if (pos == 0) {
        return isDigitChar(s[0]);
    }

    if (!isDigitChar(s[pos])) {
        return false;
    }

    if (!isOperatorChar(s[pos - 1])) {
        return false;
    }

    return isValidRec(s, pos - 2);
}

static int evalRec(const char* s, int pos) {
    if (pos == 0) {
        return s[0] - '0';
    }

    int left = evalRec(s, pos - 2);
    int digit = s[pos] - '0';

    if (s[pos - 1] == '+') {
        return left + digit;
    }

    return left - digit;
}

static bool evaluateExpression(const char* s, int& value) {
    int len = recursiveLength(s);

    if (!isValidRec(s, len - 1)) {
        return false;
    }

    value = evalRec(s, len - 1);
    return true;
}

static void generateRec(char* s, int index, int length) {
    if (index == length) {
        s[index] = '\0';
        return;
    }

    if (index % 2 == 0) {
        s[index] = static_cast<char>('0' + randomInt(0, 9));
    } else {
        s[index] = randomInt(0, 1) == 0 ? '+' : '-';
    }

    generateRec(s, index + 1, length);
}

static void generateRandomExpression(char* s, int bufferSize) {
    int terms = randomInt(1, 10);
    int length = 2 * terms - 1;

    if (length >= bufferSize) {
        length = bufferSize - 1;
    }

    if (length < 1) {
        length = 1;
    }

    if (length % 2 == 0) {
        --length;
    }

    generateRec(s, 0, length);
}

static void printRecur14Result(bool valid, const char* expr, int value) {
    std::ofstream out("output_recur14.txt");

    std::cout << "\nРезультат:\n";
    std::cout << "Выражение: " << expr << '\n';

    if (!valid) {
        std::cout << "Ошибка: недопустимое выражение.\n";

        if (out) {
            out << "Error\n";
        }

        return;
    }

    std::cout << "Значение: " << value << '\n';

    if (out) {
        out << value << '\n';
    }
}

void runRecur14(int mode) {
    char expr[EXPRESSION_MAX];
    expr[0] = '\0';

    bool inputOk = false;

    if (mode == 1) {
        inputOk = readNonEmptyString("Введите выражение: ", expr, EXPRESSION_MAX);
    } else if (mode == 2) {
        generateRandomExpression(expr, EXPRESSION_MAX);
        inputOk = true;
        std::cout << "\nСлучайное выражение: " << expr << '\n';
    } else if (mode == 3) {
        char fileName[256];

        if (!readFileName("Введите имя файла: ", fileName, 256)) {
            return;
        }

        inputOk = readFirstLineFromFile(fileName, expr, EXPRESSION_MAX);

        if (!inputOk) {
            std::cout << "Не удалось прочитать выражение из файла.\n";
            return;
        }
    }

    if (!inputOk) {
        return;
    }

    int value = 0;
    bool valid = evaluateExpression(expr, value);

    printRecur14Result(valid, expr, value);
}