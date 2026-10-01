#include "treefun11.h"
#include "binarytree.h"
#include "treeinput.h"
#include "utils.h"
#include <iostream>

static int findIndex(TNode** arr, int n, TNode* node) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == node) {
            return i;
        }
    }

    return -1;
}

void runTreeFun11(int mode) {
    BinaryTree tree;
    int fileIndex = 0;
    bool indexKnown = false;

    if (!buildArbitraryTreeWithIndex(mode, tree, fileIndex, indexKnown)) {
        return;
    }

    int n = tree.count();

    if (n == 0) {
        std::cout << "Дерево пустое.\n";
        return;
    }

    TNode** arr = new TNode*[n];
    TNode** parents = new TNode*[n];

    tree.fillLevelOrder(arr, parents);

    std::cout << "\nДерево:\n";
    tree.printGraphical(std::cout);

    std::cout << "\nНумерация вершин (по слоям):\n";

    for (int i = 0; i < n; ++i) {
        std::cout << i << " -> " << arr[i]->getData() << '\n';
    }

    int startIndex = 0;

    if (indexKnown) {
        if (fileIndex < 0 || fileIndex >= n) {
            std::cout << "Некорректный номер стартовой вершины.\n";
            delete[] arr;
            delete[] parents;
            return;
        }

        startIndex = fileIndex;
    } else if (mode == 1) {
        if (!readInt("Номер стартовой вершины: ", 0, n - 1, startIndex)) {
            delete[] arr;
            delete[] parents;
            return;
        }
    } else {
        initRandom();
        startIndex = randomInt(0, n - 1);
    }

    std::cout << "\nПожар начинается в вершине со значением "
              << arr[startIndex]->getData() << ".\n";

    bool* visited = new bool[n];
    int* queue = new int[n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    int front = 0;
    int back = 0;

    queue[back++] = startIndex;
    visited[startIndex] = true;

    std::cout << "\nПорядок сгорания вершин:\n";

    bool first = true;

    while (front < back) {
        int index = queue[front++];
        TNode* node = arr[index];

        if (!first) {
            std::cout << ' ';
        }

        std::cout << node->getData();
        first = false;

        TNode* neighbors[3];
        neighbors[0] = node->getLeft();
        neighbors[1] = node->getRight();
        neighbors[2] = parents[index];

        for (int i = 0; i < 3; ++i) {
            if (!neighbors[i]) {
                continue;
            }

            int j = findIndex(arr, n, neighbors[i]);

            if (j >= 0 && !visited[j]) {
                visited[j] = true;
                queue[back++] = j;
            }
        }
    }

    std::cout << '\n';

    delete[] arr;
    delete[] parents;
    delete[] visited;
    delete[] queue;
}