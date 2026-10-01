#include "treework1.h"
#include "binarytree.h"
#include "treechecker.h"
#include "treeinput.h"
#include <iostream>

void runTreeWork1(int mode) {
    BinaryTree tree;

    if (!buildArbitraryTree(mode, tree)) {
        return;
    }

    if (tree.isEmpty()) {
        std::cout << "Дерево пустое.\n";
        return;
    }

    std::cout << "\nДерево до преобразования:\n";
    tree.printGraphical();

    std::cout << "\nСодержимое дерева при концевом обходе (снизу-вверх):\n";
    tree.printPostorder();

    TreeChecker::checkPostorder(tree);

    std::cout << "\nДерево после преобразования:\n";
    tree.printGraphical();
}