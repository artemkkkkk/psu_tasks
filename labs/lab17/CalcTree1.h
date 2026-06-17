#pragma once
#include "ExpressionTree.h"

class CalcTree1 : public ExpressionTree {
private:
    void removeSubtraction(TreeNode* node);

public:
    void transform() override;
};