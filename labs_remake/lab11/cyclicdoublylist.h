#ifndef CYCLICDOUBLYLIST_H
#define CYCLICDOUBLYLIST_H

#include "nodes.h"

class CyclicDoublyList {
private:
    TNode2* first;
    int size;

    void clear();
    void removeNode(TNode2* node);

public:
    CyclicDoublyList();
    CyclicDoublyList(const CyclicDoublyList& other);
    ~CyclicDoublyList();

    CyclicDoublyList& operator=(const CyclicDoublyList& other);

    bool isEmpty() const;
    int count() const;

    void append(int value);
    bool removeFirst(int& value);
    TNode2* findFirstValue(int value) const;

    TNode2* firstNode() const;
    TNode2* lastNode() const;

    int removeEqualNeighborValues();

    void print() const;
};

#endif