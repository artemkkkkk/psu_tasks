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
        BinaryTree::dispose(node);
        return 0;
    }

    if (hasLeft) {
        node->Left = buildManualRec(ok);

        if (!ok) {
            BinaryTree::dispose(node);
            return 0;
        }
    }

    bool hasRight = false;

    if (!readYesNo("Есть правый потомок у вершины? (y/n): ", hasRight)) {
        ok = false;
        BinaryTree::dispose(node);
        return 0;
    }

    if (hasRight) {
        node->Right = buildManualRec(ok);

        if (!ok) {
            BinaryTree::dispose(node);
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
        node->Left = buildRandomRec(remaining);
    }

    if (remaining > 0 && randomInt(0, 100) < 70) {
        node->Right = buildRandomRec(remaining);
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

    node->Left = readPreorder(in, ok);

    if (!ok) {
        BinaryTree::dispose(node);
        return 0;
    }

    node->Right = readPreorder(in, ok);

    if (!ok) {
        BinaryTree::dispose(node);
        return 0;
    }

    return node;
}

bool buildArbitraryTree(int mode, BinaryTree& tree) {
    if (mode == 1) {
        bool ok = true;

        std::cout << "Построение дерева (корень задаётся первым).\n";

        TNode* root = buildManualRec(ok);

        if (!ok) {
            return false;
        }

        tree.attachRoot(root);
        return true;
    }

    if (mode == 2) {
        initRandom();

        int remaining = randomInt(7, 12);
        TNode* root = buildRandomRec(remaining);

        tree.attachRoot(root);

        std::cout << "\nСлучайное дерево построено. Количество вершин: "
                  << tree.count() << '\n';
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

    bool ok = true;
    TNode* root = readPreorder(in, ok);

    if (!ok) {
        std::cout << "Не удалось прочитать дерево из файла.\n";
        return false;
    }

    tree.attachRoot(root);
    return true;
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

bool buildBSTTree(int mode, BinaryTree& tree) {
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