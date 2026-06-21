#pragma once
#include "BinaryTree.h"
#include "DynamicArray.h"
#include "Map.h"

class TreeFun11 : public BinaryTree {
private:
    void buildParentMap(TreeNode* node, TreeNode* parent, Map<TreeNode*, TreeNode*>& parentMap);
    DynamicArray<TreeNode*> getNeighbors(TreeNode* node, const Map<TreeNode*, TreeNode*>& parentMap);

public:
    DynamicArray<DynamicArray<int>> simulateFire(TreeNode* startNode);
    TreeNode* findNode(int value) const;
    DynamicArray<int> getFireOrder(int startValue);
};