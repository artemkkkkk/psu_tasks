#include "treefun3.h"
#include "binarytree.h"
#include "treeinput.h"
#include "inorderiterator.h"
#include <iostream>

void runTreeFun3(int mode) {
    BinaryTree tree;

    if (!buildArbitraryTree(mode, tree)) {
        return;
    }

    if (tree.isEmpty()) {
        std::cout << "Дерево пустое.\n";
        return;
    }

    std::cout << "\nДерево:\n";
    tree.printGraphical(std::cout);

    int n = tree.count();

    InOrderIterator iterator(tree.getRoot(), n);

    std::cout << "\nОбход лево-корень-право через итератор:\n";

    bool first = true;

    while (iterator.hasNext()) {
        if (!first) {
            std::cout << ' ';
        }

        std::cout << iterator.next();
        first = false;
    }

    std::cout << '\n';
}