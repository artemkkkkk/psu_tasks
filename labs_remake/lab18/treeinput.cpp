#include "treeinput.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

static TNode* buildManualRec(bool& ok) {
    if (!ok) {
        return 0;
    }

    int value = 0;

    if (!readInt("Введите значение вершины: ", -10000, 10000, value)) {
        ok = false;
        return 0;
    }

    TNode* node = BinaryTree::createNode(value);

    bool hasLeft = false;

    if (!readYesNo("Есть левый потомок у вершины? (y/n): ", hasLeft)) {
        ok = false;
        BinaryTree::disposeNode(node);
        return 0;
    }

    if (hasLeft) {
        node->setLeft(buildManualRec(ok));

        if (!ok) {
            BinaryTree::disposeNode(node);
            return 0;
        }
    }

    bool hasRight = false;

    if (!readYesNo("Есть правый потомок у вершины? (y/n): ", hasRight)) {
        ok = false;
        BinaryTree::disposeNode(node);
        return 0;
    }

    if (hasRight) {
        node->setRight(buildManualRec(ok));

        if (!ok) {
            BinaryTree::disposeNode(node);
            return 0;
        }
    }

    return node;
}

static TNode* buildRandomRec(int& remaining) {
    if (remaining <= 0) {
        return 0;
    }

    --remaining;

    TNode* node = BinaryTree::createNode(randomInt(-99, 99));

    if (remaining > 0 && randomInt(0, 100) < 70) {
        node->setLeft(buildRandomRec(remaining));
    }

    if (remaining > 0 && randomInt(0, 100) < 70) {
        node->setRight(buildRandomRec(remaining));
    }

    return node;
}

static TNode* readPreorder(std::ifstream& in, bool& ok) {
    if (!ok) {
        return 0;
    }

    char token[64];

    if (!(in >> token)) {
        ok = false;
        return 0;
    }

    if (token[0] == '#' && token[1] == '\0') {
        return 0;
    }

    char* end = 0;
    long value = std::strtol(token, &end, 10);

    if (!end || *end != '\0') {
        ok = false;
        return 0;
    }

    TNode* node = BinaryTree::createNode(static_cast<int>(value));

    node->setLeft(readPreorder(in, ok));

    if (!ok) {
        BinaryTree::disposeNode(node);
        return 0;
    }

    node->setRight(readPreorder(in, ok));

    if (!ok) {
        BinaryTree::disposeNode(node);
        return 0;
    }

    return node;
}

static bool buildArbitraryManual(BinaryTree& tree) {
    bool ok = true;

    std::cout << "Построение дерева (корень задаётся первым).\n";

    TNode* root = buildManualRec(ok);

    if (!ok) {
        return false;
    }

    tree.attachRoot(root);
    return true;
}

static bool buildArbitraryRandom(BinaryTree& tree) {
    initRandom();

    int remaining = randomInt(7, 12);
    TNode* root = buildRandomRec(remaining);

    tree.attachRoot(root);

    std::cout << "\nСлучайное дерево построено. Количество вершин: "
              << tree.count() << '\n';

    return true;
}

static bool buildArbitraryFile(
    BinaryTree& tree,
    const char* fileName,
    bool readIndex,
    int& index
) {
    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    bool ok = true;
    TNode* root = readPreorder(in, ok);

    if (!ok) {
        std::cout << "Не удалось прочитать дерево из файла.\n";
        return false;
    }

    if (readIndex) {
        if (!(in >> index)) {
            std::cout << "Не удалось прочитать номер стартовой вершины.\n";
            BinaryTree::disposeNode(root);
            return false;
        }
    }

    tree.attachRoot(root);
    return true;
}

bool buildArbitraryTreeWithIndex(int mode, BinaryTree& tree, int& index, bool& indexKnown) {
    indexKnown = false;

    if (mode == 1) {
        return buildArbitraryManual(tree);
    }

    if (mode == 2) {
        return buildArbitraryRandom(tree);
    }

    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    bool ok = buildArbitraryFile(tree, fileName, true, index);

    if (ok) {
        indexKnown = true;
    }

    return ok;
}

bool buildArbitraryTree(int mode, BinaryTree& tree) {
    int dummy = 0;
    bool known = false;

    if (mode == 1) {
        return buildArbitraryManual(tree);
    }

    if (mode == 2) {
        return buildArbitraryRandom(tree);
    }

    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    return buildArbitraryFile(tree, fileName, false, dummy);
}

static bool readBSTValues(std::ifstream* in, BinaryTree& tree) {
    int count = 0;

    if (in) {
        if (!(*in >> count)) {
            std::cout << "Не удалось прочитать количество чисел.\n";
            return false;
        }
    } else {
        if (!readInt("Количество чисел: ", 1, 50, count)) {
            return false;
        }
    }

    if (count < 1 || count > 100000) {
        std::cout << "Некорректное количество чисел.\n";
        return false;
    }

    for (int i = 0; i < count; ++i) {
        int value = 0;

        if (in) {
            if (!(*in >> value)) {
                std::cout << "Не удалось прочитать числа.\n";
                return false;
            }
        } else {
            std::cout << "Число " << (i + 1) << ": ";

            if (!readIntNoPrompt(-10000, 10000, value)) {
                return false;
            }
        }

        if (!tree.insertBST(value)) {
            std::cout << "Значение " << value
                      << " уже присутствует в дереве и пропущено.\n";
        }
    }

    return true;
}

bool buildBST(int mode, BinaryTree& tree) {
    if (mode == 1) {
        return readBSTValues(0, tree) && !tree.isEmpty();
    }

    if (mode == 2) {
        initRandom();

        int count = randomInt(7, 15);

        for (int i = 0; i < count; ++i) {
            int value = 0;
            int attempts = 0;

            do {
                value = randomInt(-99, 99);
                ++attempts;
            } while (!tree.insertBST(value) && attempts < 200);
        }

        std::cout << "\nСлучайное дерево поиска построено. Количество вершин: "
                  << tree.count() << '\n';

        return !tree.isEmpty();
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

    return readBSTValues(&in, tree) && !tree.isEmpty();
}