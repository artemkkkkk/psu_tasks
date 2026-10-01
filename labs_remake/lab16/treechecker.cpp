#include "treechecker.h"
#include <iostream>

int TreeChecker::fillPostorder(TNode* node, int* buffer, int index) {
    if (!node) {
        return index;
    }

    index = fillPostorder(node->Left, buffer, index);
    index = fillPostorder(node->Right, buffer, index);
    buffer[index++] = node->Data;
    return index;
}

int TreeChecker::fillPostorderIterative(TNode* root, int* buffer, TNode** stack1, TNode** stack2) {
    int top1 = 0;
    int top2 = 0;

    stack1[top1++] = root;

    while (top1 > 0) {
        TNode* node = stack1[--top1];
        stack2[top2++] = node;

        if (node->Left) {
            stack1[top1++] = node->Left;
        }

        if (node->Right) {
            stack1[top1++] = node->Right;
        }
    }

    int index = 0;

    while (top2 > 0) {
        buffer[index++] = stack2[--top2]->Data;
    }

    return index;
}

bool TreeChecker::checkPostorder(const BinaryTree& tree) {
    int n = tree.count();

    if (n == 0) {
        std::cout << "Проверка: дерево пустое, обход пуст. Проверка пройдена.\n";
        return true;
    }

    int* recursiveSeq = new int[n];
    int* iterativeSeq = new int[n];
    TNode** stack1 = new TNode*[n];
    TNode** stack2 = new TNode*[n];

    fillPostorder(tree.getRoot(), recursiveSeq, 0);
    fillPostorderIterative(tree.getRoot(), iterativeSeq, stack1, stack2);

    bool same = true;

    for (int i = 0; i < n; ++i) {
        if (recursiveSeq[i] != iterativeSeq[i]) {
            same = false;
            break;
        }
    }

    if (same) {
        std::cout << "Проверка: последовательности концевого обхода совпадают ("
                  << n << " элементов). Проверка пройдена.\n";
    } else {
        std::cout << "Проверка: последовательности концевого обхода НЕ совпадают!\n";
    }

    delete[] recursiveSeq;
    delete[] iterativeSeq;
    delete[] stack1;
    delete[] stack2;

    return same;
}

int TreeChecker::depthByLevels(TNode* root, TNode** queue, int* levels, int capacity) {
    if (!root) {
        return -1;
    }

    int front = 0;
    int back = 0;

    queue[back] = root;
    levels[back] = 0;
    ++back;

    int maxLevel = 0;

    while (front < back) {
        TNode* node = queue[front];
        int level = levels[front];
        ++front;

        if (level > maxLevel) {
            maxLevel = level;
        }

        if (node->Left && back < capacity) {
            queue[back] = node->Left;
            levels[back] = level + 1;
            ++back;
        }

        if (node->Right && back < capacity) {
            queue[back] = node->Right;
            levels[back] = level + 1;
            ++back;
        }
    }

    return maxLevel;
}

bool TreeChecker::checkDepth(const BinaryTree& tree) {
    int n = tree.count();

    if (n == 0) {
        std::cout << "Проверка: дерево пустое, глубина не определена. Проверка пройдена.\n";
        return true;
    }

    TNode** queue = new TNode*[n];
    int* levels = new int[n];

    int recursiveDepth = tree.depth();
    int levelDepth = depthByLevels(tree.getRoot(), queue, levels, n);

    bool same = recursiveDepth == levelDepth;

    std::cout << "Проверка: глубина рекурсивно = " << recursiveDepth
              << ", по уровням = " << levelDepth << ". "
              << (same ? "Проверка пройдена." : "Проверка НЕ пройдена!") << '\n';

    delete[] queue;
    delete[] levels;

    return same;
}

int TreeChecker::minByFullScan(TNode* root, TNode** stack, int capacity) {
    if (!root) {
        return 0;
    }

    int top = 0;
    stack[top++] = root;

    int minValue = root->Data;

    while (top > 0) {
        TNode* node = stack[--top];

        if (node->Data < minValue) {
            minValue = node->Data;
        }

        if (node->Left && top < capacity) {
            stack[top++] = node->Left;
        }

        if (node->Right && top < capacity) {
            stack[top++] = node->Right;
        }
    }

    return minValue;
}

bool TreeChecker::secondMinByFullScan(TNode* root, TNode** stack, int capacity, int& value) {
    if (!root) {
        return false;
    }

    int top = 0;
    stack[top++] = root;

    int min1 = 0;
    int min2 = 0;
    bool has1 = false;
    bool has2 = false;

    while (top > 0) {
        TNode* node = stack[--top];
        int v = node->Data;

        if (!has1 || v < min1) {
            if (has1) {
                min2 = min1;
                has2 = true;
            }

            min1 = v;
            has1 = true;
        } else if (v != min1) {
            if (!has2 || v < min2) {
                min2 = v;
                has2 = true;
            }
        }

        if (node->Left && top < capacity) {
            stack[top++] = node->Left;
        }

        if (node->Right && top < capacity) {
            stack[top++] = node->Right;
        }
    }

    if (!has2) {
        return false;
    }

    value = min2;
    return true;
}

bool TreeChecker::isBSTRec(TNode* node, const int* minBound, const int* maxBound) {
    if (!node) {
        return true;
    }

    if (minBound && node->Data <= *minBound) {
        return false;
    }

    if (maxBound && node->Data >= *maxBound) {
        return false;
    }

    return isBSTRec(node->Left, minBound, &node->Data) &&
           isBSTRec(node->Right, &node->Data, maxBound);
}

bool TreeChecker::isBST(const BinaryTree& tree) {
    return isBSTRec(tree.getRoot(), 0, 0);
}

bool TreeChecker::checkMin(const BinaryTree& tree) {
    int n = tree.count();

    if (n == 0) {
        std::cout << "Проверка: дерево пустое.\n";
        return true;
    }

    TNode** stack = new TNode*[n];

    int fastMin = tree.minFast();
    int fullMin = minByFullScan(tree.getRoot(), stack, n);
    bool bst = isBST(tree);

    bool same = fastMin == fullMin;

    std::cout << "Проверка: дерево " << (bst ? "является" : "НЕ является")
              << " деревом поиска.\n";
    std::cout << "Проверка: минимум по левой ветви = " << fastMin
              << ", полным обходом = " << fullMin << ". "
              << (same && bst ? "Проверка пройдена." : "Проверка НЕ пройдена!") << '\n';

    delete[] stack;

    return same && bst;
}

bool TreeChecker::checkSecondMin(const BinaryTree& tree) {
    int n = tree.count();

    if (n == 0) {
        std::cout << "Проверка: дерево пустое.\n";
        return true;
    }

    TNode** stack = new TNode*[n];

    int fastValue = 0;
    int fullValue = 0;

    bool fastOk = tree.secondMinFast(fastValue);
    bool fullOk = secondMinByFullScan(tree.getRoot(), stack, n, fullValue);
    bool bst = isBST(tree);

    bool same = fastOk == fullOk && (!fastOk || fastValue == fullValue);

    std::cout << "Проверка: дерево " << (bst ? "является" : "НЕ является")
              << " деревом поиска.\n";

    if (same && fastOk) {
        std::cout << "Проверка: второй минимум быстрым методом = " << fastValue
                  << ", полным обходом = " << fullValue << ". Проверка пройдена.\n";
    } else if (same) {
        std::cout << "Проверка: второго минимума не существует. Проверка пройдена.\n";
    } else {
        std::cout << "Проверка: результаты НЕ совпадают!\n";
    }

    delete[] stack;

    return same && bst;
}