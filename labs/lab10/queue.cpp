#include "queue.h"
#include <iostream>

using namespace std;

Queue::Queue() : Head(nullptr), Tail(nullptr) {}

Queue::~Queue() {
    int val;
    while (Dequeue(val));
}

void Queue::Enqueue(int value) {
    QNode* newNode = new QNode;
    newNode->Data = value;
    newNode->Next = nullptr;
    
    if (Tail) {
        Tail->Next = newNode;
    } else {
        Head = newNode;
    }
    Tail = newNode;
}

bool Queue::Dequeue(int& value) {
    if (Head == nullptr) return false;
    QNode* temp = Head;
    value = Head->Data;
    Head = Head->Next;
    if (Head == nullptr) Tail = nullptr;
    delete temp;
    return true;
}

bool Queue::IsEmpty() const {
    return Head == nullptr;
}

QNode* Queue::GetHeadPtr() const {
    return Head;
}

QNode* Queue::GetTailPtr() const {
    return Tail;
}

int Queue::Size() const {
    int count = 0;
    QNode* curr = Head;
    while (curr) {
        count++;
        curr = curr->Next;
    }
    return count;
}

void Queue::SolveDynamic24(Queue& q1, Queue& q2) {
    if (q1.IsEmpty() || q2.IsEmpty()) {
        cout << "Очереди должны быть непустыми." << endl;
        return;
    }
    
    Queue result;
    
    while (!q1.IsEmpty() && !q2.IsEmpty()) {
        QNode* n1 = q1.Head;
        q1.Head = q1.Head->Next;
        if (q1.Head == nullptr) q1.Tail = nullptr;
        n1->Next = nullptr; // Отрываем
        
        QNode* n2 = q2.Head;
        q2.Head = q2.Head->Next;
        if (q2.Head == nullptr) q2.Tail = nullptr;
        n2->Next = nullptr; // Отрываем
        
        if (result.Tail) {
            result.Tail->Next = n1;
            result.Tail = n1;
            result.Tail->Next = n2;
            result.Tail = n2;
        } else {
            result.Head = n1;
            n1->Next = n2;
            result.Tail = n2;
        }
    }
    
    cout << "Результирующая очередь создана." << endl;
    cout << "Head: " << result.GetHeadPtr() << ", Tail: " << result.GetTailPtr() << endl;
    
    cout << "Содержимое: ";
    int val;
    while (result.Dequeue(val)) {
        cout << val << " ";
    }
    cout << endl;
}

void runDynamic24() {
    cout << "\n--- Задача Dynamic24 ---" << endl;
    Queue q1, q2;
    
    cout << "Заполните первую очередь (введите 3 числа):" << endl;
    for(int i=0; i<3; ++i) {
        int x; cin >> x;
        q1.Enqueue(x);
    }
    
    cout << "Заполните вторую очередь (введите 3 числа):" << endl;
    for(int i=0; i<3; ++i) {
        int x; cin >> x;
        q2.Enqueue(x);
    }
    
    Queue::SolveDynamic24(q1, q2);
}