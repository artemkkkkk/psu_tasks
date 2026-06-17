#include "TreeNode.h"

TreeNode::TreeNode(int value) : value(value), isVariable(false), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(const std::string& varName) : value(0), isVariable(true), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {}

int TreeNode::getValue() const {
    return value;
}

bool TreeNode::isVar() const {
    return isVariable;
}

TreeNode* TreeNode::getLeft() const {
    return left;
}

TreeNode* TreeNode::getRight() const {
    return right;
}

void TreeNode::setValue(int value) {
    this->value = value;
    this->isVariable = false;
}

void TreeNode::setLeft(TreeNode* left) {
    this->left = left;
}

void TreeNode::setRight(TreeNode* right) {
    this->right = right;
}

void TreeNode::setVariable(bool isVariable) {
    this->isVariable = isVariable;
}

bool TreeNode::isOperator() const {
    return value < 0;
}

std::string TreeNode::getOperatorSymbol() const {
    switch (value) {
        case -1: return "+";
        case -2: return "-";
        case -3: return "*";
        case -4: return "/";
        case -5: return "%";
        case -6: return "^";
        default: return "?";
    }
}