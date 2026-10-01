#ifndef NAMERING_H
#define NAMERING_H

#include "nodes.h"

class NameRing {
private:
    NameNode* head;
    NameNode* tail;
    int size;

    void clear();

public:
    NameRing();
    NameRing(const NameRing& other);
    ~NameRing();

    NameRing& operator=(const NameRing& other);

    bool isEmpty() const;
    int count() const;

    bool append(const char* name);
    bool removeFirst(char* nameBuffer, int bufferSize);
    NameNode* findFirstName(const char* name) const;

    void print() const;
    bool eliminateWithStep(int step, const char* outputFile);
};

#endif