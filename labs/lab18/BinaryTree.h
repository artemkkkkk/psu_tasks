#pragma once
#include "TreeNode.h"
#include <iostream>
#include <string>

class BinaryTree {
protected:
    TreeNode* root;

    void destroyTree(TreeNode* node);
    TreeNode* copyTree(TreeNode* node);
    void printGraphical(TreeNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const;
    void insertSearchHelper(TreeNode** node, int value);
    void inOrderCollect(TreeNode* node, TreeNode*& prev, TreeNode*& head, TreeNode*& tail);

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    virtual ~BinaryTree();

    TreeNode* getRoot() const;
    void setRoot(TreeNode* root);
    bool isEmpty() const;

    void insertSearch(int value);
    void buildFromValues(const int* values, int count);

    void printGraphical(std::ostream& out) const;
};