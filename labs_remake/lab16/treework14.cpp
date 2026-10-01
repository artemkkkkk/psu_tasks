#include "treework14.h"
#include "binarytree.h"
#include "treechecker.h"
#include "treeinput.h"
#include <iostream>

void runTreeWork14(int mode) {
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

    std::cout << "\nГлубина дерева: " << tree.depth() << '\n';

    TreeChecker::checkDepth(tree);

    std::cout << "\nДерево после преобразования:\n";
    tree.printGraphical();
}