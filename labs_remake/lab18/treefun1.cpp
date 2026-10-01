#include "treefun1.h"
#include "binarytree.h"
#include "treeinput.h"
#include <iostream>

static void bstToListRec(TNode* node, TNode*& prev, TNode*& head) {
    if (!node) {
        return;
    }

    bstToListRec(node->getLeft(), prev, head);

    if (prev) {
        prev->setRight(node);
    } else {
        head = node;
    }

    node->setLeft(prev);
    prev = node;

    bstToListRec(node->getRight(), prev, head);
}

void runTreeFun1(int mode) {
    BinaryTree tree;

    if (!buildBST(mode, tree)) {
        return;
    }

    if (tree.isEmpty()) {
        std::cout << "Дерево пустое.\n";
        return;
    }

    std::cout << "\nИсходное дерево поиска:\n";
    tree.printGraphical(std::cout);

    TNode* prev = 0;
    TNode* head = 0;

    bstToListRec(tree.getRoot(), prev, head);

    if (prev) {
        prev->setRight(0);
    }

    tree.release();

    std::cout << "\nПолучившийся двусвязный список:\n";

    bool first = true;
    TNode* cur = head;

    while (cur) {
        if (!first) {
            std::cout << ' ';
        }

        std::cout << cur->getData();
        first = false;
        cur = cur->getRight();
    }

    std::cout << '\n';

    while (head) {
        TNode* next = head->getRight();
        delete head;
        head = next;
    }
}