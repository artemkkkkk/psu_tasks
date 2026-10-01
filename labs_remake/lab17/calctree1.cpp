#include "calctree1.h"
#include "calctree.h"
#include "treechecker.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

static int tokenizeLine(const char* line, int* tokens, int maxTokens) {
    int count = 0;
    const char* p = line;

    while (*p && count < maxTokens) {
        while (*p == ' ' || *p == '\t') {
            ++p;
        }

        if (!*p) {
            break;
        }

        char* end = 0;
        long value = std::strtol(p, &end, 10);

        if (end == p) {
            return -1;
        }

        tokens[count++] = static_cast<int>(value);
        p = end;
    }

    return count;
}

static bool inputManual(int* tokens, int& count) {
    char line[512];

    std::cout << "Формат: операнды 0..9; операции: -1 (+), -2 (-), -3 (*).\n";

    if (!readNonEmptyString("Введите выражение в обратной польской записи: ", line, 512)) {
        return false;
    }

    count = tokenizeLine(line, tokens, 256);

    if (count <= 0) {
        std::cout << "Не удалось распознать выражение.\n";
        return false;
    }

    return true;
}

static TNode* genRec(int& remaining) {
    if (remaining <= 1 || randomInt(0, 100) < 30) {
        --remaining;
        return CalcTree::createNode(randomInt(0, 9));
    }

    --remaining;

    const char ops[3] = { '+', '-', '*' };
    TNode* node = CalcTree::createNode(ops[randomInt(0, 2)]);

    node->setLeft(genRec(remaining));
    node->setRight(genRec(remaining));

    return node;
}

static int fillTokens(TNode* node, int* tokens, int index) {
    if (!node) {
        return index;
    }

    if (node->isLeaf()) {
        tokens[index++] = node->getData();
        return index;
    }

    index = fillTokens(node->getLeft(), tokens, index);
    index = fillTokens(node->getRight(), tokens, index);

    int code = node->getData() == '+' ? -1 : (node->getData() == '-' ? -2 : -3);
    tokens[index++] = code;

    return index;
}

static bool inputRandom(int* tokens, int& count) {
    initRandom();

    int remaining = randomInt(5, 11);
    TNode* temp = genRec(remaining);

    count = fillTokens(temp, tokens, 0);
    CalcTree::disposeNode(temp);

    std::cout << "\nСлучайное выражение в обратной польской записи: ";

    for (int i = 0; i < count; ++i) {
        std::cout << tokens[i] << ' ';
    }

    std::cout << '\n';

    return true;
}

static bool inputFile(int* tokens, int& count) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    count = 0;
    int t = 0;

    while (in >> t) {
        if (count >= 256) {
            std::cout << "Слишком длинное выражение.\n";
            return false;
        }

        tokens[count++] = t;
    }

    if (count == 0) {
        std::cout << "Файл пуст.\n";
        return false;
    }

    return true;
}

void runCalcTree1(int mode) {
    static int tokens[256];
    int count = 0;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(tokens, count);
    } else if (mode == 2) {
        ok = inputRandom(tokens, count);
    } else if (mode == 3) {
        ok = inputFile(tokens, count);
    }

    if (!ok) {
        return;
    }

    CalcTree original;

    if (!original.buildFromPostfix(tokens, count)) {
        std::cout << "Некорректная запись выражения.\n";
        return;
    }

    CalcTree transformed = original;
    transformed.eliminateSubtraction();

    std::cout << "\nДерево до преобразования:\n";
    original.printGraphical(std::cout);

    std::cout << "\nДерево после преобразования:\n";
    transformed.printGraphical(std::cout);

    std::cout << "\nАдрес корня полученного дерева: "
              << static_cast<const void*>(transformed.getRoot()) << '\n';

    TreeChecker::checkCalcTree1(tokens, count, original, transformed);
}