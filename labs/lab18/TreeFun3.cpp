#include "TreeFun3.h"

TreeFun3Iterator::TreeFun3Iterator(TreeNode* root) {
    pushLeft(root);
}

void TreeFun3Iterator::pushLeft(TreeNode* node) {
    while (node != nullptr) {
        stack.push_back(node);
        node = node->getLeft();
    }
}

bool TreeFun3Iterator::hasNext() const {
    return !stack.empty();
}

int TreeFun3Iterator::next() {
    TreeNode* node = stack.back();
    stack.pop_back();
    int value = node->getValue();
    pushLeft(node->getRight());
    return value;
}

TreeFun3Iterator TreeFun3::begin() const {
    return TreeFun3Iterator(root);
}