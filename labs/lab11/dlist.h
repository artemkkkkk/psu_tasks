#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct DNode {
    int Data;
    DNode* Prev;
    DNode* Next;
};

class DoublyLinkedList {
private:
    DNode* Head;
    DNode* Tail;
    bool IsCircular;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void Append(int value);
    void PrintForward() const;
    void PrintBackward() const;

    DNode* GetHead() const { return Head; }
    DNode* GetTail() const { return Tail; }
    void SetCircular(bool val) { IsCircular = val; }
    bool GetCircular() const { return IsCircular; }

    void SolveListWork42();
    void SolveListWork43();
    void SolveListWork46();

    DNode* CreateBarrierList();
};

void runListWork42();
void runListWork43();
void runListWork46();

#endif // DLIST_H