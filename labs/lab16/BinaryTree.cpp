#include "BinaryTree.h"
#include <queue>
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
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current->getLeft() == nullptr) {
            current->setLeft(newNode);
            return;
        } else {
            q.push(current->getLeft());
        }
        if (current->getRight() == nullptr) {
            current->setRight(newNode);
            return;
        } else {
            q.push(current->getRight());
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

void BinaryTree::postOrderTraversal(TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }
    postOrderTraversal(node->getLeft(), result);
    postOrderTraversal(node->getRight(), result);
    result.push_back(node->getValue());
}

std::vector<int> BinaryTree::getPostOrder() const {
    std::vector<int> result;
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

int BinaryTree::findSecondMinimum(TreeNode* node, TreeNode*& parent, bool& found) const {
    if (node == nullptr) {
        throw std::runtime_error("Дерево пустое");
    }
    TreeNode* current = node;
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

int BinaryTree::getSecondMinimum() const {
    TreeNode* parent = nullptr;
    bool found = false;
    return findSecondMinimum(root, parent, found);
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
    std::vector<int> result = getPostOrder();
    out << "Концевой обход: [";
    for (size_t i = 0; i < result.size(); ++i) {
        out << result[i];
        if (i < result.size() - 1) {
            out << ", ";
        }
    }
    out << "]" << std::endl;
}