#ifndef STACK_H
#define STACK_H

#include "nodes.h"

class Stack {
private:
    TNode* top;
    int size;

    static TNode* cloneNodes(TNode* node);
    void clear();

public:
    Stack();
    Stack(const Stack& other);
    ~Stack();

    Stack& operator=(const Stack& other);

    bool isEmpty() const;
    int count() const;

    void push(int value);
    bool pop(int& value);

    TNode* topNode() const;
    void print() const;
};

#endif