#ifndef CLIST_H
#define CLIST_H

#include <iostream>
#include <fstream>
#include <string>

struct CNode {
    int Data;
    CNode* Next;
};

class CircularSingleList {
private:
    CNode* Head;
public:
    CircularSingleList();
    ~CircularSingleList();

    void Append(int value);
    void SolveListWork66(const std::string& filename);
};

void runListWork66();

#endif // CLIST_H