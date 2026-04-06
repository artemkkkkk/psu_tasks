#include "list.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList() : Head(nullptr) {}

LinkedList::~LinkedList() {
    LNode* curr = Head;
    while (curr) {
        LNode* next = curr->Next;
        delete curr;
        curr = next;
    }
}

void LinkedList::Append(int value) {
    LNode* newNode = new LNode;
    newNode->Data = value;
    newNode->Next = nullptr;
    
    if (!Head) {
        Head = newNode;
    } else {
        LNode* curr = Head;
        while (curr->Next) curr = curr->Next;
        curr->Next = newNode;
    }
}

LNode* LinkedList::GetHead() const {
    return Head;
}

LNode* LinkedList::GetNthNode(int n) const {
    if (n <= 0) return nullptr;
    LNode* curr = Head;
    for (int i = 1; i < n; ++i) {
        if (!curr) return nullptr;
        curr = curr->Next;
    }
    return curr;
}

LNode* LinkedList::GetLastNode() const {
    if (!Head) return nullptr;
    LNode* curr = Head;
    while (curr->Next) curr = curr->Next;
    return curr;
}

void LinkedList::Print() const {
    LNode* curr = Head;
    while (curr) {
        cout << curr->Data << " -> ";
        curr = curr->Next;
    }
    cout << "nullptr" << endl;
}

void LinkedList::SolveListWork1() {
    LNode* p2 = GetNthNode(2);
    cout << "Указатель на 2-й элемент: " << p2 << endl;
    if (p2) cout << "Значение: " << p2->Data << endl;
}

void LinkedList::SolveListWork22(int M) {
    LNode* curr = Head;
    int count = 0;
    while (curr) {
        count++;
        if (count % 2 == 0) {
            LNode* newNode = new LNode;
            newNode->Data = M;
            newNode->Next = curr->Next;
            curr->Next = newNode;
            curr = newNode->Next;
        } else {
            curr = curr->Next;
        }
    }
    cout << "Список после вставки " << M << " после каждого 2-го:" << endl;
    Print();
    cout << "Указатель на последний элемент: " << GetLastNode() << endl;
}

void LinkedList::SolveListWork59(int K, int M) {
    if (K <= 0) return;
    LNode* curr = Head;
    int count = 0;
    while (curr) {
        count++;
        if (count % K == 0) {
            LNode* newNode = new LNode;
            newNode->Data = M;
            newNode->Next = curr->Next;
            curr->Next = newNode;
            curr = newNode->Next;
        } else {
            curr = curr->Next;
        }
    }
    cout << "Список после вставки " << M << " после каждого " << K << "-го:" << endl;
    Print();
    cout << "Указатель на последний элемент: " << GetLastNode() << endl;
}

void runListWork1() {
    cout << "\n--- Задача ListWork1 ---" << endl;
    LinkedList list;
    list.Append(10);
    list.Append(20);
    list.Append(30);
    cout << "Список: ";
    list.Print();
    list.SolveListWork1();
}

void runListWork22() {
    cout << "\n--- Задача ListWork22 ---" << endl;
    LinkedList list;
    cout << "Введите элементы списка (0 для окончания): ";
    int x;
    while (cin >> x && x != 0) {
        list.Append(x);
    }
    
    int M;
    cout << "Введите M для вставки: ";
    cin >> M;
    
    cout << "Исходный список: ";
    list.Print();
    list.SolveListWork22(M);
}

void runListWork59() {
    cout << "\n--- Задача ListWork59 ---" << endl;
    LinkedList list;
    cout << "Введите элементы списка (0 для окончания): ";
    int x;
    while (cin >> x && x != 0) {
        list.Append(x);
    }
    
    int K, M;
    cout << "Введите K (шаг) и M (значение): ";
    cin >> K >> M;
    
    cout << "Исходный список: ";
    list.Print();
    list.SolveListWork59(K, M);
}