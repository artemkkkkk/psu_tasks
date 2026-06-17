#include "CalcTree1.h"
#include <stdexcept>

void CalcTree1::removeSubtraction(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    removeSubtraction(node->getLeft());
    removeSubtraction(node->getRight());
    if (node->getValue() == -2) {
        int leftVal = evaluate(node->getLeft(), 0);
        int rightVal = evaluate(node->getRight(), 0);
        int result = leftVal - rightVal;
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        node->setValue(result);
        node->setLeft(nullptr);
        node->setRight(nullptr);
    }
}

void CalcTree1::transform() {
    removeSubtraction(root);
}