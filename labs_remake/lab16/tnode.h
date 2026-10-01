#ifndef TNODE_H
#define TNODE_H

struct TNode {
    int Data;
    TNode* Left;
    TNode* Right;

    TNode(int value = 0) : Data(value), Left(0), Right(0) {}
};

#endif