#include "binarytree.h"
#include <iostream>

TNode* BinaryTree::clone(TNode* node) {
    if (!node) {
        return 0;
    }

    TNode* copy = new TNode(node->Data);
    copy->Left = clone(node->Left);
    copy->Right = clone(node->Right);
    return copy;
}

void BinaryTree::dispose(TNode* node) {
    if (!node) {
        return;
    }

    dispose(node->Left);
    dispose(node->Right);
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
        if (value == cur->Data) {
            return false;
        }

        if (value < cur->Data) {
            if (!cur->Left) {
                cur->Left = new TNode(value);
                return true;
            }

            cur = cur->Left;
        } else {
            if (!cur->Right) {
                cur->Right = new TNode(value);
                return true;
            }

            cur = cur->Right;
        }
    }
}

void BinaryTree::printGraphicalRec(TNode* node, int level, int parentValue, bool hasParent, std::ostream& out) {
    if (!node) {
        return;
    }

    printGraphicalRec(node->Right, level + 1, node->Data, true, out);

    for (int i = 0; i < level; ++i) {
        out << "    ";
    }

    out << node->Data;

    if (hasParent) {
        out << " [<- " << parentValue << "]";
    } else {
        out << " [root]";
    }

    out << '\n';

    printGraphicalRec(node->Left, level + 1, node->Data, true, out);
}

void BinaryTree::printGraphical(std::ostream& out) const {
    if (!root) {
        out << "(пустое дерево)\n";
        return;
    }

    printGraphicalRec(root, 0, 0, false, out);
}

void BinaryTree::postorderRec(TNode* node, bool& first) {
    if (!node) {
        return;
    }

    postorderRec(node->Left, first);
    postorderRec(node->Right, first);

    if (!first) {
        std::cout << ' ';
    }

    std::cout << node->Data;
    first = false;
}

void BinaryTree::printPostorder() const {
    bool first = true;
    postorderRec(root, first);
    std::cout << '\n';
}

int BinaryTree::depthRec(TNode* node) {
    if (!node) {
        return -1;
    }

    int leftDepth = depthRec(node->Left);
    int rightDepth = depthRec(node->Right);

    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int BinaryTree::depth() const {
    return depthRec(root);
}

int BinaryTree::countRec(TNode* node) {
    if (!node) {
        return 0;
    }

    return 1 + countRec(node->Left) + countRec(node->Right);
}

int BinaryTree::minFast() const {
    if (!root) {
        return 0;
    }

    TNode* cur = root;

    while (cur->Left) {
        cur = cur->Left;
    }

    return cur->Data;
}

bool BinaryTree::secondMinFast(int& value) const {
    if (!root) {
        return false;
    }

    TNode* cur = root;
    TNode* parent = 0;

    while (cur->Left) {
        parent = cur;
        cur = cur->Left;
    }

    if (cur->Right) {
        TNode* sub = cur->Right;

        while (sub->Left) {
            sub = sub->Left;
        }

        value = sub->Data;
        return true;
    }

    if (parent) {
        value = parent->Data;
        return true;
    }

    return false;
}