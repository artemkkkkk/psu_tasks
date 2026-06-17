#include "CalcTree23.h"

void CalcTree23::swapAddition(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    swapAddition(node->getLeft());
    swapAddition(node->getRight());
    if (node->getValue() == -1 && node->getRight() != nullptr && node->getRight()->isVar()) {
        TreeNode* temp = node->getLeft();
        node->setLeft(node->getRight());
        node->setRight(temp);
    }
}

void CalcTree23::transform() {
    swapAddition(root);
}