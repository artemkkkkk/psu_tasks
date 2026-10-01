#include "treework17.h"
#include "binarytree.h"
#include "treechecker.h"
#include "treeinput.h"
#include <iostream>

void runTreeWork17(int mode) {
    BinaryTree tree;

    if (!buildBSTTree(mode, tree)) {
        return;
    }

    if (tree.isEmpty()) {
        std::cout << "Дерево пустое.\n";
        return;
    }

    std::cout << "\nДерево до преобразования:\n";
    tree.printGraphical();

    int value = 0;

    std::cout << "\nВторое минимальное значение в дереве: ";

    if (tree.secondMinFast(value)) {
        std::cout << value << '\n';
    } else {
        std::cout << "не существует (в дереве меньше двух вершин)";
        std::cout << '\n';
    }

    TreeChecker::checkSecondMin(tree);

    std::cout << "\nДерево после преобразования:\n";
    tree.printGraphical();
}