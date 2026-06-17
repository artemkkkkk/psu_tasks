#pragma once
#include "TreeNode.h"
#include <iostream>

class DoublyList {
private:
    TreeNode* head;
    TreeNode* tail;

public:
    DoublyList();
    DoublyList(TreeNode* head, TreeNode* tail);

    TreeNode* getHead() const;
    TreeNode* getTail() const;

    void printForward(std::ostream& out) const;
    void printBackward(std::ostream& out) const;
};