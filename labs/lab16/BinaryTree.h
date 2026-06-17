#pragma once
#include "TreeNode.h"
#include <vector>
#include <string>

class BinaryTree {
protected:
    TreeNode* root;

    void destroyTree(TreeNode* node);
    TreeNode* copyTree(TreeNode* node);
    void printGraphical(TreeNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const;
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

    void postOrderTraversal(TreeNode* node, std::vector<int>& result) const;
    std::vector<int> getPostOrder() const;

    int calculateDepth(TreeNode* node) const;
    int getDepth() const;

    int findSecondMinimum(TreeNode* node, TreeNode*& parent, bool& found) const;
    int getSecondMinimum() const;

    void printGraphical(std::ostream& out) const;
    void printPostOrder(std::ostream& out) const;
};