#include "calctree23.h"
#include "calctree.h"
#include "treechecker.h"
#include "utils.h"
#include <iostream>
#include <fstream>

struct InfixParser {
    const char* s;
    int pos;
    bool ok;

    void skipSpaces() {
        while (s[pos] == ' ' || s[pos] == '\t') {
            ++pos;
        }
    }

    TNode* parseAtom() {
        skipSpaces();

        char c = s[pos];

        if (c == 'x' || c == 'X') {
            ++pos;
            return CalcTree::createNode(VAR_X);
        }

        if (c >= '0' && c <= '9') {
            int value = 0;

            while (s[pos] >= '0' && s[pos] <= '9') {
                value = value * 10 + (s[pos] - '0');
                ++pos;
            }

            if (value < 1 || value > 30) {
                ok = false;
                return 0;
            }

            return CalcTree::createNode(value);
        }

        if (c == '(') {
            ++pos;

            TNode* expr = parseExpr();
            if (!ok) {
                return 0;
            }

            skipSpaces();

            if (s[pos] != ')') {
                ok = false;
                CalcTree::disposeNode(expr);
                return 0;
            }

            ++pos;
            return expr;
        }

        ok = false;
        return 0;
    }

    TNode* parsePower() {
        TNode* left = parseAtom();
        if (!ok) {
            return 0;
        }

        while (true) {
            skipSpaces();

            if (s[pos] == '^') {
                ++pos;

                TNode* right = parseAtom();
                if (!ok) {
                    CalcTree::disposeNode(left);
                    return 0;
                }

                TNode* node = CalcTree::createNode('^');
                node->setLeft(left);
                node->setRight(right);
                left = node;
            } else {
                break;
            }
        }

        return left;
    }

    TNode* parseTerm() {
        TNode* left = parsePower();
        if (!ok) {
            return 0;
        }

        while (true) {
            skipSpaces();

            char c = s[pos];

            if (c == '*' || c == '/' || c == '%') {
                ++pos;

                TNode* right = parsePower();
                if (!ok) {
                    CalcTree::disposeNode(left);
                    return 0;
                }

                TNode* node = CalcTree::createNode(c);
                node->setLeft(left);
                node->setRight(right);
                left = node;
            } else {
                break;
            }
        }

        return left;
    }

    TNode* parseExpr() {
        TNode* left = parseTerm();
        if (!ok) {
            return 0;
        }

        while (true) {
            skipSpaces();

            char c = s[pos];

            if (c == '+' || c == '-') {
                ++pos;

                TNode* right = parseTerm();
                if (!ok) {
                    CalcTree::disposeNode(left);
                    return 0;
                }

                TNode* node = CalcTree::createNode(c);
                node->setLeft(left);
                node->setRight(right);
                left = node;
            } else {
                break;
            }
        }

        return left;
    }

    TNode* parse() {
        pos = 0;
        ok = true;

        TNode* result = parseExpr();

        if (!ok) {
            return 0;
        }

        skipSpaces();

        if (s[pos] != '\0') {
            ok = false;
            CalcTree::disposeNode(result);
            return 0;
        }

        return result;
    }
};

static bool parseExpression(const char* line, CalcTree& tree) {
    InfixParser parser;
    parser.s = line;

    TNode* root = parser.parse();

    if (!parser.ok || !root) {
        std::cout << "Некорректное выражение.\n";
        return false;
    }

    tree.attachRoot(root);
    return true;
}

static bool inputManual(CalcTree& tree, int& x) {
    char line[256];

    std::cout << "Допустимые символы: числа 1..30, x, операции + - * / % ^, скобки.\n";

    if (!readNonEmptyString("Введите инфиксное выражение: ", line, 256)) {
        return false;
    }

    if (!readInt("Значение переменной x: ", -100, 100, x)) {
        return false;
    }

    return parseExpression(line, tree);
}

static TNode* genRec23(int& remaining) {
    if (remaining <= 1 || randomInt(0, 100) < 30) {
        --remaining;

        if (randomInt(0, 100) < 25) {
            return CalcTree::createNode(VAR_X);
        }

        return CalcTree::createNode(randomInt(1, 9));
    }

    --remaining;

    const char ops[6] = { '+', '-', '*', '/', '%', '^' };
    TNode* node = CalcTree::createNode(ops[randomInt(0, 5)]);

    node->setLeft(genRec23(remaining));
    node->setRight(genRec23(remaining));

    return node;
}

static bool inputRandom(CalcTree& tree, int& x) {
    initRandom();

    int remaining = randomInt(5, 11);
    TNode* root = genRec23(remaining);

    tree.attachRoot(root);
    x = randomInt(1, 9);

    std::cout << "\nСлучайное выражение: ";
    tree.printInfix(std::cout);
    std::cout << '\n';

    std::cout << "x = " << x << '\n';

    return true;
}

static bool inputFile(CalcTree& tree, int& x, char* outName) {
    char inName[256];

    if (!readFileName("Введите имя входного файла FN1: ", inName, 256)) {
        return false;
    }

    if (!readFileName("Введите имя выходного файла FN2: ", outName, 256)) {
        return false;
    }

    std::ifstream in(inName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    char line[256];
    line[0] = '\0';

    while (in.getline(line, 256)) {
        trimString(line);

        if (line[0] != '\0') {
            break;
        }
    }

    if (line[0] == '\0') {
        std::cout << "Не удалось прочитать выражение.\n";
        return false;
    }

    if (!(in >> x)) {
        std::cout << "Не удалось прочитать значение x.\n";
        return false;
    }

    return parseExpression(line, tree);
}

void runCalcTree23(int mode) {
    CalcTree original;
    int x = 0;

    char outName[256];
    copyString(outName, 256, "output_calctree23.txt");

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(original, x);
    } else if (mode == 2) {
        ok = inputRandom(original, x);
    } else if (mode == 3) {
        ok = inputFile(original, x, outName);
    }

    if (!ok) {
        return;
    }

    std::cout << "\nДерево до преобразования:\n";
    original.printGraphical(std::cout);

    int value = 0;
    bool hasValue = original.evaluate(x, value);

    std::cout << "\nЗначение выражения при x = " << x << ": ";

    if (hasValue) {
        std::cout << value;
    } else {
        std::cout << "ошибка вычисления (деление на ноль)";
    }

    std::cout << '\n';

    CalcTree transformed = original;
    transformed.swapAxToXa();

    std::cout << "\nДерево после преобразования:\n";
    transformed.printGraphical(std::cout);

    std::cout << "\nФормы дерева после преобразования:\n";

    std::cout << "Префиксная: ";
    transformed.printPrefix(std::cout);
    std::cout << '\n';

    std::cout << "Постфиксная: ";
    transformed.printPostfix(std::cout);
    std::cout << '\n';

    std::cout << "Инфиксная со скобками: ";
    transformed.printInfix(std::cout);
    std::cout << '\n';

    std::ofstream out(outName);

    if (out) {
        if (hasValue) {
            out << value << '\n';
        } else {
            out << "Ошибка вычисления" << '\n';
        }

        out << "Префиксная форма: ";
        transformed.printPrefix(out);
        out << '\n';

        out << "Постфиксная форма: ";
        transformed.printPostfix(out);
        out << '\n';

        out << "Инфиксная форма: ";
        transformed.printInfix(out);
        out << '\n';

        std::cout << "Результаты записаны в файл " << outName << '\n';
    } else {
        std::cout << "Не удалось создать выходной файл.\n";
    }

    TreeChecker::checkCalcTree23(original, transformed, x);
}