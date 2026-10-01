#ifndef LIST_H
#define LIST_H

#include "nodes.h"

class List {
private:
    TNode* head;
    TNode* tail;
    int size;

    void clear();

public:
    List();
    List(const List& other);
    ~List();

    List& operator=(const List& other);

    bool isEmpty() const;
    int count() const;

    void pushBack(int value);
    bool removeFirst(int& value);

    TNode* findFirstValue(int value) const;
    TNode* at(int index) const;
    TNode* lastNode() const;

    void insertAfterEveryK(int k, int value);

    void print() const;
};

#endif