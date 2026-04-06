#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack() : Top(nullptr) {}

Stack::~Stack() {
    int val;
    while (Pop(val));
}

void Stack::Push(int value) {
    TNode* newNode = new TNode;
    newNode->Data = value;
    newNode->Next = Top;
    Top = newNode;
}

bool Stack::Pop(int& value) {
    if (Top == nullptr) return false;
    TNode* temp = Top;
    value = Top->Data;
    Top = Top->Next;
    delete temp;
    return true;
}

bool Stack::IsEmpty() const {
    return Top == nullptr;
}

TNode* Stack::GetTopPtr() const {
    return Top;
}

void Stack::SolveDynamic3(int D) {
    if (IsEmpty()) {
        cout << "Стек пуст. По условию стек непустой, но мы обработаем этот случай." << endl;
    }
    Push(D);
    cout << "Элемент " << D << " добавлен." << endl;
    cout << "Адрес новой вершины (P2): " << GetTopPtr() << endl;
}

void runDynamic3() {
    cout << "\n--- Задача Dynamic3 ---" << endl;
    Stack s;
    
    s.Push(10);
    s.Push(20);
    
    cout << "Исходная вершина стека: " << s.GetTopPtr() << endl;
    
    int D;
    cout << "Введите число D для добавления в стек: ";
    cin >> D;
    
    s.SolveDynamic3(D);
}