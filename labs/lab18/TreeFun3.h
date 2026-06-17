#pragma once
#include "BinaryTree.h"
#include <vector>

class TreeFun3Iterator {
private:
    std::vector<TreeNode*> stack;

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