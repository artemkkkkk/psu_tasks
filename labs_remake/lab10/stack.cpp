#include "stack.h"
#include <iostream>

TNode* Stack::cloneNodes(TNode* node) {
    if (!node) {
        return 0;
    }

    TNode* copy = new TNode(node->Data);
    copy->Next = cloneNodes(node->Next);
    return copy;
}

void Stack::clear() {
    while (top) {
        TNode* old = top;
        top = top->Next;
        delete old;
    }

    size = 0;
}

Stack::Stack() : top(0), size(0) {}

Stack::Stack(const Stack& other) {
    top = cloneNodes(other.top);
    size = other.size;
}

Stack::~Stack() {
    clear();
}

Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        top = cloneNodes(other.top);
        size = other.size;
    }

    return *this;
}

bool Stack::isEmpty() const {
    return top == 0;
}

int Stack::count() const {
    return size;
}

void Stack::push(int value) {
    TNode* node = new TNode(value);
    node->Next = top;
    top = node;
    ++size;
}

bool Stack::pop(int& value) {
    if (!top) {
        return false;
    }

    value = top->Data;
    TNode* old = top;
    top = top->Next;
    delete old;
    --size;

    return true;
}

TNode* Stack::topNode() const {
    return top;
}

void Stack::print() const {
    TNode* cur = top;

    while (cur) {
        std::cout << cur->Data << ' ';
        cur = cur->Next;
    }

    std::cout << '\n';
}