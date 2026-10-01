#ifndef TREEINPUT_H
#define TREEINPUT_H

#include "binarytree.h"

bool buildArbitraryTree(int mode, BinaryTree& tree);
bool buildArbitraryTreeWithIndex(int mode, BinaryTree& tree, int& index, bool& indexKnown);
bool buildBST(int mode, BinaryTree& tree);

#endif