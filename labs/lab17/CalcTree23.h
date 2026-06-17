#pragma once
#include "ExpressionTree.h"

class CalcTree23 : public ExpressionTree {
private:
    void swapAddition(TreeNode* node);

public:
    void transform() override;
};