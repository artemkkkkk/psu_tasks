#ifndef RING_H
#define RING_H

#include "nodes.h"

class Ring {
private:
    TNode* head;
    TNode* tail;
    int size;

    void clear();

public:
    Ring();
    Ring(const Ring& other);
    ~Ring();

    Ring& operator=(const Ring& other);

    bool isEmpty() const;
    int count() const;

    void append(int value);
    bool removeFirst(int& value);
    TNode* findFirstValue(int value) const;

    void print() const;
    bool eliminateWithStep(int step, const char* outputFile);
};

#endif