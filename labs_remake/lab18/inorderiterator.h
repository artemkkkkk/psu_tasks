#ifndef INORDERITERATOR_H
#define INORDERITERATOR_H

#include "tnode.h"

class InOrderIterator {
private:
    TNode** stack;
    int top;

    void pushLeftSpine(TNode* node);

public:
    InOrderIterator(TNode* root, int capacity);
    ~InOrderIterator();

    bool hasNext() const;
    int next();
};

#endif