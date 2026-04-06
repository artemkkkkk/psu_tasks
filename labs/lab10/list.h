#ifndef LIST_H
#define LIST_H

struct LNode {
    int Data;
    LNode* Next;
};

class LinkedList {
private:
    LNode* Head;
public:
    LinkedList();
    ~LinkedList();

    void Append(int value);
    void InsertAfter(LNode* prev, int value);
    void InsertBeforeSecond(int value);

    LNode* GetHead() const;
    LNode* GetNthNode(int n) const;
    LNode* GetLastNode() const;

    void SolveListWork1();
    void SolveListWork22(int M);
    void SolveListWork59(int K, int M);

    void Print() const;
};

void runListWork1();
void runListWork22();
void runListWork59();

#endif // LIST_H