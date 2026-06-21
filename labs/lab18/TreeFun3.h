#pragma once
#include "BinaryTree.h"
#include "Stack.h"

class TreeFun3Iterator {
private:
    Stack<TreeNode*> stack;

    void pushLeft(TreeNode* node);

public:
    TreeFun3Iterator(TreeNode* root);

    bool hasNext() const;
    int next();
};

class TreeFun3 : public BinaryTree {
public:
    TreeFun3Iterator begin() const;
};