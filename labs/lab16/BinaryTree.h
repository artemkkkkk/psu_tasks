#pragma once
#include "TreeNode.h"
#include "DynamicArray.h"
#include <string>
#include <iostream>

class BinaryTree {
protected:
    TreeNode* root;

    void destroyTree(TreeNode* node);
    TreeNode* copyTree(TreeNode* node);
    void printGraphical(TreeNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const;
    void postOrderTraversal(TreeNode* node, DynamicArray<int>& result) const;
    int calculateDepth(TreeNode* node) const;
    int countNodes(TreeNode* node) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    virtual ~BinaryTree();

    TreeNode* getRoot() const;
    void setRoot(TreeNode* root);
    bool isEmpty() const;

    void insertLevelOrder(int value);
    void insertSearch(int value);

    DynamicArray<int> getPostOrder() const;
    int getDepth() const;
    int getSecondMinimum() const;

    void printGraphical(std::ostream& out) const;
    void printPostOrder(std::ostream& out) const;
};