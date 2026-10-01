#include "inorderiterator.h"

InOrderIterator::InOrderIterator(TNode* root, int capacity) {
    stack = new TNode*[capacity > 0 ? capacity : 1];
    top = 0;
    pushLeftSpine(root);
}

InOrderIterator::~InOrderIterator() {
    delete[] stack;
}

void InOrderIterator::pushLeftSpine(TNode* node) {
    while (node) {
        stack[top++] = node;
        node = node->getLeft();
    }
}

bool InOrderIterator::hasNext() const {
    return top > 0;
}

int InOrderIterator::next() {
    TNode* node = stack[--top];
    pushLeftSpine(node->getRight());
    return node->getData();
}