#ifndef QUEUE_H
#define QUEUE_H

#include "nodes.h"

class Queue {
private:
    TNode* head;
    TNode* tail;
    int size;

    void clear();

public:
    Queue();
    Queue(const Queue& other);
    ~Queue();

    Queue& operator=(const Queue& other);

    bool isEmpty() const;
    int count() const;

    void pushBack(int value);
    bool popFront(int& value);

    TNode* headNode() const;
    TNode* tailNode() const;

    void release();
    void adopt(TNode* newHead, TNode* newTail, int newSize);

    void print() const;
};

#endif