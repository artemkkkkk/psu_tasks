#pragma once
#include "TreeNode.h"
#include "DynamicArray.h"
#include <string>
#include <iostream>

class ExpressionTree {
protected:
    TreeNode* root;

    void destroyTree(TreeNode* node);
    TreeNode* copyTree(TreeNode* node);
    void printGraphical(TreeNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const;
    int evaluate(TreeNode* node, int xValue) const;
    void toPrefix(TreeNode* node, DynamicArray<std::string>& result) const;
    void toPostfix(TreeNode* node, DynamicArray<std::string>& result) const;
    void toInfix(TreeNode* node, std::string& result) const;

public:
    ExpressionTree();
    ExpressionTree(const ExpressionTree& other);
    ExpressionTree& operator=(const ExpressionTree& other);
    virtual ~ExpressionTree();

    TreeNode* getRoot() const;
    void setRoot(TreeNode* root);
    bool isEmpty() const;

    void buildFromPostfix(const std::string& expression);
    void buildFromInfix(const std::string& expression);

    int calculate(int xValue) const;

    virtual void transform() = 0;

    void printGraphical(std::ostream& out) const;
    std::string getPrefixNotation() const;
    std::string getPostfixNotation() const;
    std::string getInfixNotation() const;
};