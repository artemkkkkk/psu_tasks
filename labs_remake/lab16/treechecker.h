#ifndef TREECHECKER_H
#define TREECHECKER_H

#include "binarytree.h"

class TreeChecker {
private:
    static int fillPostorder(TNode* node, int* buffer, int index);
    static int fillPostorderIterative(TNode* root, int* buffer, TNode** stack1, TNode** stack2);
    static int depthByLevels(TNode* root, TNode** queue, int* levels, int capacity);
    static int minByFullScan(TNode* root, TNode** stack, int capacity);
    static bool secondMinByFullScan(TNode* root, TNode** stack, int capacity, int& value);
    static bool isBSTRec(TNode* node, const int* minBound, const int* maxBound);

public:
    static bool checkPostorder(const BinaryTree& tree);
    static bool checkDepth(const BinaryTree& tree);
    static bool checkMin(const BinaryTree& tree);
    static bool checkSecondMin(const BinaryTree& tree);
    static bool isBST(const BinaryTree& tree);
};

#endif