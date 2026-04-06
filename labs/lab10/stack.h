#ifndef STACK_H
#define STACK_H

struct TNode {
    int Data;
    TNode* Next;
};

class Stack {
private:
    TNode* Top;
public:
    Stack();
    ~Stack();

    void Push(int value);
    bool Pop(int& value); // Возвращает false, если стек пуст
    bool IsEmpty() const;
    TNode* GetTopPtr() const;

    void SolveDynamic3(int D);
};

void runDynamic3();

#endif // STACK_H