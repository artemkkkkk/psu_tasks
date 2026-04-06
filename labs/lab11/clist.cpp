#include "clist.h"

using namespace std;

CircularSingleList::CircularSingleList() : Head(nullptr) {}

CircularSingleList::~CircularSingleList() {
    if (!Head) return;
    CNode* curr = Head->Next;
    while (curr != Head) {
        CNode* next = curr->Next;
        delete curr;
        curr = next;
    }
    delete Head;
}

void CircularSingleList::Append(int value) {
    CNode* newNode = new CNode;
    newNode->Data = value;
    
    if (!Head) {
        Head = newNode;
        Head->Next = Head;
    } else {
        CNode* tail = Head;
        while (tail->Next != Head) {
            tail = tail->Next;
        }
        tail->Next = newNode;
        newNode->Next = Head;
    }
}

void CircularSingleList::SolveListWork66(const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Ошибка создания файла " << filename << endl;
        return;
    }

    if (!Head) return;

    CNode* curr = Head;
    CNode* prev = nullptr; // Для удаления

    while (Head != nullptr && Head->Next != Head) {

        CNode* toDelete = Head;
        
        fout << toDelete->Data;
        
        if (toDelete->Next == toDelete) {
            fout << endl;
            delete toDelete;
            Head = nullptr;
            break;
        }
        
        CNode* prev = Head;
        while (prev->Next != toDelete) {
            prev = prev->Next;
        }
        
        prev->Next = toDelete->Next;
        Head = toDelete->Next;
        delete toDelete;
        
        if (Head) {
            Head = Head->Next;
            Head = Head->Next;

            fout << " ";
        }
    }
    
    if (Head) {
        fout << Head->Data << endl;
        delete Head;
        Head = nullptr;
    }
    
    fout.close();
    cout << "Результат записан в " << filename << endl;
}

void runListWork66() {
    cout << "\n--- Задача ListWork66 ---" << endl;
    CircularSingleList list;
    
    cout << "Введите элементы кольца (0 для окончания): ";
    int x;
    while (cin >> x && x != 0) {
        list.Append(x);
    }
    
    list.SolveListWork66("output_listwork66.txt");
}