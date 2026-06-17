#pragma once
#include <string>

class TreeNode {
private:
    int value;
    bool isVariable;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode(int value);
    TreeNode(const std::string& varName);
    ~TreeNode();

    int getValue() const;
    bool isVar() const;
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    void setValue(int value);
    void setLeft(TreeNode* left);
    void setRight(TreeNode* right);
    void setVariable(bool isVariable);

    bool isOperator() const;
    std::string getOperatorSymbol() const;
};