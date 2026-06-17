#include "TreeFun1.h"

DoublyList TreeFun1::convertToList() {
    if (root == nullptr) {
        return DoublyList();
    }
    TreeNode* prev = nullptr;
    TreeNode* head = nullptr;
    TreeNode* tail = nullptr;
    inOrderCollect(root, prev, head, tail);
    if (tail != nullptr) {
        tail->setRight(nullptr);
    }
    root = nullptr;
    return DoublyList(head, tail);
}