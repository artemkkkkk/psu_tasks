#ifndef QUEUE_H
#define QUEUE_H

struct QNode {
    int Data;
    QNode* Next;
};

class Queue {
private:
    QNode* Head;
    QNode* Tail;
public:
    Queue();
    ~Queue();

    void Enqueue(int value);
    bool Dequeue(int& value);
    bool IsEmpty() const;
    QNode* GetHeadPtr() const;
    QNode* GetTailPtr() const;
    int Size() const;

    static void SolveDynamic24(Queue& q1, Queue& q2);
};

void runDynamic24();

#endif // QUEUE_H