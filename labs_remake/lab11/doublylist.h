#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include "nodes.h"

class DoublyList {
private:
    TNode2* head;
    TNode2* tail;
    int size;

    void clear();

public:
    DoublyList();
    DoublyList(const DoublyList& other);
    ~DoublyList();

    DoublyList& operator=(const DoublyList& other);

    bool isEmpty() const;
    int count() const;

    void pushBack(int value);
    bool removeFirst(int& value);
    TNode2* findFirstValue(int value) const;

    TNode2* headNode() const;
    TNode2* tailNode() const;

    void release();
    TNode2* moveOddPositionsToEnd();

    void print() const;
};

#endif