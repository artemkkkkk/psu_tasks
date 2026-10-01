#ifndef NODES_H
#define NODES_H

struct TNode {
    int Data;
    TNode* Next;

    TNode(int value = 0) : Data(value), Next(0) {}
};

#endif