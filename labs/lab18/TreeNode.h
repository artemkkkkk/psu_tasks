#pragma once

class TreeNode {
private:
    int value;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode(int value);
    ~TreeNode();

    int getValue() const;
    TreeNode*& getLeft();
    TreeNode*& getRight();
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    void setValue(int value);
    void setLeft(TreeNode* left);
    void setRight(TreeNode* right);
};