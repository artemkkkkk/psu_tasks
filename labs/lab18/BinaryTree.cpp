#include "BinaryTree.h"
#include <stdexcept>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(const BinaryTree& other) : root(copyTree(other.root)) {}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

BinaryTree::~BinaryTree() {
    destroyTree(root);
}

void BinaryTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }
}

TreeNode* BinaryTree::copyTree(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TreeNode* newNode = new TreeNode(node->getValue());
    newNode->setLeft(copyTree(node->getLeft()));
    newNode->setRight(copyTree(node->getRight()));
    return newNode;
}

TreeNode* BinaryTree::getRoot() const {
    return root;
}

void BinaryTree::setRoot(TreeNode* root) {
    this->root = root;
}

bool BinaryTree::isEmpty() const {
    return root == nullptr;
}

void BinaryTree::insertSearchHelper(TreeNode** node, int value) {
    if (*node == nullptr) {
        *node = new TreeNode(value);
        return;
    }
    if (value < (*node)->getValue()) {
        insertSearchHelper(&((*node)->getLeft()), value);
    } else if (value > (*node)->getValue()) {
        insertSearchHelper(&((*node)->getRight()), value);
    }
}

void BinaryTree::insertSearch(int value) {
    insertSearchHelper(&root, value);
}

void BinaryTree::buildFromValues(const int* values, int count) {
    for (int i = 0; i < count; ++i) {
        insertSearch(values[i]);
    }
}

void BinaryTree::inOrderCollect(TreeNode* node, TreeNode*& prev, TreeNode*& head, TreeNode*& tail) {
    if (node == nullptr) {
        return;
    }
    inOrderCollect(node->getLeft(), prev, head, tail);
    if (prev != nullptr) {
        prev->setRight(node);
        node->setLeft(prev);
    } else {
        head = node;
    }
    prev = node;
    tail = node;
    inOrderCollect(node->getRight(), prev, head, tail);
}

void BinaryTree::printGraphical(TreeNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const {
    if (node == nullptr) {
        return;
    }
    out << prefix;
    out << (isLeft ? "├── " : "└── ");
    out << node->getValue() << std::endl;
    printGraphical(node->getLeft(), prefix + (isLeft ? "│   " : "    "), true, out);
    printGraphical(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, out);
}

void BinaryTree::printGraphical(std::ostream& out) const {
    if (root == nullptr) {
        out << "(пустое дерево)" << std::endl;
        return;
    }
    printGraphical(root, "", true, out);
}