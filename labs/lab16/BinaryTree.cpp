#include "BinaryTree.h"
#include "Stack.h"
#include <stdexcept>
#include <algorithm>

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

void BinaryTree::insertLevelOrder(int value) {
    TreeNode* newNode = new TreeNode(value);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    Stack<TreeNode*> q;
    Stack<TreeNode*> tempStack;
    q.push(root);
    while (true) {
        if (q.isEmpty()) break;
        TreeNode* current = q.top();
        q.pop();
        if (current->getLeft() == nullptr) {
            current->setLeft(newNode);
            return;
        } else {
            tempStack.push(current->getLeft());
        }
        if (current->getRight() == nullptr) {
            current->setRight(newNode);
            return;
        } else {
            tempStack.push(current->getRight());
        }
        while (!tempStack.isEmpty()) {
            q.push(tempStack.top());
            tempStack.pop();
        }
    }
}

void BinaryTree::insertSearch(int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }
    TreeNode* current = root;
    while (true) {
        if (value < current->getValue()) {
            if (current->getLeft() == nullptr) {
                current->setLeft(new TreeNode(value));
                return;
            }
            current = current->getLeft();
        } else if (value > current->getValue()) {
            if (current->getRight() == nullptr) {
                current->setRight(new TreeNode(value));
                return;
            }
            current = current->getRight();
        } else {
            return;
        }
    }
}

void BinaryTree::postOrderTraversal(TreeNode* node, DynamicArray<int>& result) const {
    if (node == nullptr) {
        return;
    }
    postOrderTraversal(node->getLeft(), result);
    postOrderTraversal(node->getRight(), result);
    result.pushBack(node->getValue());
}

DynamicArray<int> BinaryTree::getPostOrder() const {
    DynamicArray<int> result;
    postOrderTraversal(root, result);
    return result;
}

int BinaryTree::calculateDepth(TreeNode* node) const {
    if (node == nullptr) {
        return -1;
    }
    int leftDepth = calculateDepth(node->getLeft());
    int rightDepth = calculateDepth(node->getRight());
    return 1 + std::max(leftDepth, rightDepth);
}

int BinaryTree::getDepth() const {
    return calculateDepth(root);
}

int BinaryTree::countNodes(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodes(node->getLeft()) + countNodes(node->getRight());
}

int BinaryTree::getSecondMinimum() const {
    if (root == nullptr) {
        throw std::runtime_error("Дерево пустое");
    }
    TreeNode* current = root;
    TreeNode* prev = nullptr;
    while (current->getLeft() != nullptr) {
        prev = current;
        current = current->getLeft();
    }
    if (current->getRight() != nullptr) {
        TreeNode* rightChild = current->getRight();
        while (rightChild->getLeft() != nullptr) {
            rightChild = rightChild->getLeft();
        }
        return rightChild->getValue();
    }
    if (prev == nullptr) {
        throw std::runtime_error("В дереве только один элемент");
    }
    return prev->getValue();
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

void BinaryTree::printPostOrder(std::ostream& out) const {
    DynamicArray<int> result = getPostOrder();
    out << "Концевой обход: [";
    for (int i = 0; i < result.getSize(); ++i) {
        out << result[i];
        if (i < result.getSize() - 1) {
            out << ", ";
        }
    }
    out << "]" << std::endl;
}