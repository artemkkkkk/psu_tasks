#include "TreeNode.h"

TreeNode::TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {}

int TreeNode::getValue() const {
    return value;
}

TreeNode* TreeNode::getLeft() const {
    return left;
}

TreeNode* TreeNode::getRight() const {
    return right;
}

void TreeNode::setValue(int value) {
    this->value = value;
}

void TreeNode::setLeft(TreeNode* left) {
    this->left = left;
}

void TreeNode::setRight(TreeNode* right) {
    this->right = right;
}