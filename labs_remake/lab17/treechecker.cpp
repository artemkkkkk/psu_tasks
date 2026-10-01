#include "treechecker.h"
#include <iostream>

bool TreeChecker::evalPostfixTokens(const int* tokens, int count, int& result) {
    if (count <= 0) {
        return false;
    }

    int* stack = new int[count];
    int top = 0;
    bool ok = true;

    for (int i = 0; i < count && ok; ++i) {
        int t = tokens[i];

        if (t >= 0 && t <= 9) {
            stack[top++] = t;
        } else if (t >= -3 && t <= -1) {
            if (top < 2) {
                ok = false;
                break;
            }

            int right = stack[--top];
            int left = stack[--top];

            if (t == -1) {
                stack[top++] = left + right;
            } else if (t == -2) {
                stack[top++] = left - right;
            } else {
                stack[top++] = left * right;
            }
        } else {
            ok = false;
        }
    }

    if (ok && top == 1) {
        result = stack[0];
    } else {
        ok = false;
    }

    delete[] stack;
    return ok;
}

bool TreeChecker::checkCalcTree1(
    const int* tokens,
    int count,
    const CalcTree& original,
    const CalcTree& transformed
) {
    int valueTokens = 0;
    int valueOriginal = 0;
    int valueTransformed = 0;

    bool ok1 = evalPostfixTokens(tokens, count, valueTokens);
    bool ok2 = original.evaluate(0, valueOriginal);
    bool ok3 = transformed.evaluate(0, valueTransformed);
    bool noMinus = !transformed.containsOperator('-');

    bool same = ok1 && ok2 && ok3 && noMinus &&
                valueTokens == valueOriginal &&
                valueOriginal == valueTransformed;

    std::cout << "Проверка: значение по записи = " << valueTokens
              << ", исходного дерева = " << valueOriginal
              << ", преобразованного = " << valueTransformed << ".\n";
    std::cout << "Проверка: операция вычитания в результате отсутствует: "
              << (noMinus ? "да" : "нет") << ".\n";
    std::cout << (same ? "Проверка пройдена.\n" : "Проверка НЕ пройдена!\n");

    return same;
}

bool TreeChecker::checkCalcTree23(
    const CalcTree& original,
    const CalcTree& transformed,
    int x
) {
    bool noPattern = !transformed.containsAxPlusX();
    bool same = true;

    const int tests[5] = { x, x + 1, 1, 5, 7 };

    for (int i = 0; i < 5; ++i) {
        int a = 0;
        int b = 0;

        bool okA = original.evaluate(tests[i], a);
        bool okB = transformed.evaluate(tests[i], b);

        if (okA != okB || (okA && a != b)) {
            same = false;
        }
    }

    bool ok = same && noPattern;

    std::cout << "Проверка: поддеревьев вида A+x после преобразования нет: "
              << (noPattern ? "да" : "нет") << ".\n";
    std::cout << "Проверка: значения исходного и преобразованного деревьев совпадают "
              << "на контрольных значениях x. "
              << (ok ? "Проверка пройдена.\n" : "Проверка НЕ пройдена!\n");

    return ok;
}