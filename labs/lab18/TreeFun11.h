#pragma once
#include "BinaryTree.h"
#include <vector>
#include <map>

class TreeFun11 : public BinaryTree {
private:
    void buildParentMap(TreeNode* node, TreeNode* parent, std::map<TreeNode*, TreeNode*>& parentMap);
    std::vector<TreeNode*> getNeighbors(TreeNode* node, const std::map<TreeNode*, TreeNode*>& parentMap);

public:
    std::vector<std::vector<int>> simulateFire(TreeNode* startNode);
    TreeNode* findNode(int value) const;
    std::vector<int> getFireOrder(int startValue);
};