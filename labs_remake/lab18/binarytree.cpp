#include "binarytree.h"
#include <iostream>

TNode* BinaryTree::clone(TNode* node) {
    if (!node) {
        return 0;
    }

    TNode* copy = new TNode(node->getData());
    copy->setLeft(clone(node->getLeft()));
    copy->setRight(clone(node->getRight()));
    return copy;
}

void BinaryTree::dispose(TNode* node) {
    if (!node) {
        return;
    }

    dispose(node->getLeft());
    dispose(node->getRight());
    delete node;
}

BinaryTree::BinaryTree() : root(0) {}

BinaryTree::BinaryTree(const BinaryTree& other) : root(clone(other.root)) {}

BinaryTree::~BinaryTree() {
    dispose(root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {
        dispose(root);
        root = clone(other.root);
    }

    return *this;
}

bool BinaryTree::isEmpty() const {
    return root == 0;
}

int BinaryTree::count() const {
    return countRec(root);
}

TNode* BinaryTree::getRoot() const {
    return root;
}

void BinaryTree::attachRoot(TNode* node) {
    dispose(root);
    root = node;
}

TNode* BinaryTree::release() {
    TNode* old = root;
    root = 0;
    return old;
}

TNode* BinaryTree::createNode(int value) {
    return new TNode(value);
}

void BinaryTree::disposeNode(TNode* node) {
    dispose(node);
}

bool BinaryTree::insertBST(int value) {
    if (!root) {
        root = new TNode(value);
        return true;
    }

    TNode* cur = root;

    while (true) {
        if (value == cur->getData()) {
            return false;
        }

        if (value < cur->getData()) {
            if (!cur->getLeft()) {
                cur->setLeft(new TNode(value));
                return true;
            }

            cur = cur->getLeft();
        } else {
            if (!cur->getRight()) {
                cur->setRight(new TNode(value));
                return true;
            }

            cur = cur->getRight();
        }
    }
}

void BinaryTree::printGraphicalRec(TNode* node, int level, int parentValue, bool hasParent, std::ostream& out) {
    if (!node) {
        return;
    }

    printGraphicalRec(node->getRight(), level + 1, node->getData(), true, out);

    for (int i = 0; i < level; ++i) {
        out << "    ";
    }

    out << node->getData();

    if (hasParent) {
        out << " [<- " << parentValue << "]";
    } else {
        out << " [root]";
    }

    out << '\n';

    printGraphicalRec(node->getLeft(), level + 1, node->getData(), true, out);
}

void BinaryTree::printGraphical(std::ostream& out) const {
    if (!root) {
        out << "(пустое дерево)\n";
        return;
    }

    printGraphicalRec(root, 0, 0, false, out);
}

int BinaryTree::countRec(TNode* node) {
    if (!node) {
        return 0;
    }

    return 1 + countRec(node->getLeft()) + countRec(node->getRight());
}

void BinaryTree::fillLevelOrder(TNode** arr, TNode** parents) const {
    int n = count();

    if (n == 0 || !root) {
        return;
    }

    TNode** queue = new TNode*[n];
    TNode** parentQueue = new TNode*[n];

    int front = 0;
    int back = 0;

    queue[back] = root;
    parentQueue[back] = 0;
    ++back;

    int index = 0;

    while (front < back) {
        TNode* node = queue[front];
        TNode* parent = parentQueue[front];
        ++front;

        arr[index] = node;
        parents[index] = parent;
        ++index;

        if (node->getLeft()) {
            queue[back] = node->getLeft();
            parentQueue[back] = node;
            ++back;
        }

        if (node->getRight()) {
            queue[back] = node->getRight();
            parentQueue[back] = node;
            ++back;
        }
    }

    delete[] queue;
    delete[] parentQueue;
}