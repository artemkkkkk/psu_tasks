#include "dlist.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() : Head(nullptr), Tail(nullptr), IsCircular(false) {}

DoublyLinkedList::~DoublyLinkedList() {
    if (!Head) return;
    
    DNode* curr = Head;
    if (IsCircular) {
        Tail->Next = nullptr;
        Head->Prev = nullptr;
    }
    
    while (curr) {
        DNode* next = curr->Next;
        delete curr;
        curr = next;
    }
}

void DoublyLinkedList::Append(int value) {
    DNode* newNode = new DNode;
    newNode->Data = value;
    newNode->Next = nullptr;
    newNode->Prev = Tail;

    if (Tail) {
        Tail->Next = newNode;
    } else {
        Head = newNode;
    }
    Tail = newNode;

    if (IsCircular) {
        Tail->Next = Head;
        Head->Prev = Tail;
    }
}

void DoublyLinkedList::PrintForward() const {
    if (!Head) return;
    DNode* curr = Head;
    do {
        cout << curr->Data << " ";
        curr = curr->Next;
    } while (curr != Head && curr != nullptr);
    cout << endl;
}

void DoublyLinkedList::SolveListWork42() {
    if (!Head || !IsCircular) {
        cout << "Список пуст или не циклический." << endl;
        return;
    }

    DNode* curr = Head;
    DNode* start = Head;

    vector<DNode*> toDelete;
    
    DNode* iter = Head;
    do {
        if (iter->Prev->Data == iter->Next->Data) {
            toDelete.push_back(iter);
        }
        iter = iter->Next;
    } while (iter != Head);

    for (DNode* node : toDelete) {
        DNode* prev = node->Prev;
        DNode* next = node->Next;
        
        prev->Next = next;
        next->Prev = prev;
        
        if (node == Head) {
            Head = next;
            if (toDelete.size() == 1 && next == node) {
                 Head = nullptr;
                 Tail = nullptr;
            }
        }
        if (node == Tail) {
            Tail = prev;
        }
        
        delete node;
    }
    
    if (!Head) {
        Tail = nullptr;
        IsCircular = false;
    } else {
         Tail->Next = Head;
         Head->Prev = Tail;
    }

    cout << "Список после ListWork42: ";
    PrintForward();
}

void DoublyLinkedList::SolveListWork43() {
    if (!Head) return;

    vector<DNode*> oddNodes;
    vector<DNode*> evenNodes;
    
    DNode* curr = Head;
    int pos = 1;
    
    do {
        if (pos % 2 != 0) {
            oddNodes.push_back(curr);
        } else {
            evenNodes.push_back(curr);
        }
        curr = curr->Next;
        pos++;
    } while (curr != Head && curr != nullptr);
    
    if (IsCircular) {
        Tail->Next = nullptr;
        Head->Prev = nullptr;
        IsCircular = false;
    }

    vector<DNode*> newOrder;
    newOrder.insert(newOrder.end(), evenNodes.begin(), evenNodes.end());
    newOrder.insert(newOrder.end(), oddNodes.begin(), oddNodes.end());
    
    if (newOrder.empty()) return;

    Head = newOrder[0];
    Head->Prev = nullptr;
    
    for (size_t i = 0; i < newOrder.size(); ++i) {
        if (i > 0) {
            newOrder[i]->Prev = newOrder[i-1];
            newOrder[i-1]->Next = newOrder[i];
        }
        newOrder[i]->Next = nullptr;
    }
    
    Tail = newOrder.back();
    Tail->Next = nullptr;
    
    cout << "Список после ListWork43: ";
    PrintForward();
}

DNode* DoublyLinkedList::CreateBarrierList() {
    if (IsCircular) {
        cout << "Список уже циклический." << endl;
        return nullptr;
    }

    DNode* barrier = new DNode;
    barrier->Data = 0;
    
    if (!Head) {
        barrier->Next = barrier;
        barrier->Prev = barrier;
        Head = barrier;
        Tail = barrier;
        IsCircular = true;
        return barrier;
    }
    
    barrier->Next = Head;
    barrier->Prev = Tail;
    
    Head->Prev = barrier;
    Tail->Next = barrier;
    
    IsCircular = true;
    
    cout << "Барьерный элемент создан. Адрес: " << barrier << endl;
    return barrier;
}

void DoublyLinkedList::SolveListWork46() {
    DNode* barrier = CreateBarrierList();
    if (barrier) {
        cout << "Список стал циклическим с барьером." << endl;
        cout << "Содержимое (начиная с Head): ";
        DNode* curr = Head;
        if (curr == barrier) curr = curr->Next;
        
        DNode* start = curr;
        do {
             cout << curr->Data << " ";
             curr = curr->Next;
        } while (curr != barrier && curr != start);
        cout << endl;
    }
}

void runListWork42() {
    cout << "\n--- Задача ListWork42 ---" << endl;
    DoublyLinkedList list;
    list.SetCircular(true);
    
    cout << "Введите элементы циклического списка (0 для окончания): ";
    int x;
    while (cin >> x && x != 0) {
        list.Append(x);
    }
    
    cout << "Исходный список: ";
    list.PrintForward();
    list.SolveListWork42();
}

void runListWork43() {
    cout << "\n--- Задача ListWork43 ---" << endl;
    DoublyLinkedList list;
    
    cout << "Введите элементы списка (0 для окончания): ";
    int x;
    while (cin >> x && x != 0) {
        list.Append(x);
    }
    
    cout << "Исходный список: ";
    list.PrintForward();
    list.SolveListWork43();
}

void runListWork46() {
    cout << "\n--- Задача ListWork46 ---" << endl;
    DoublyLinkedList list;
    
    cout << "Введите элементы линейного списка (0 для окончания): ";
    int x;
    while (cin >> x && x != 0) {
        list.Append(x);
    }
    
    cout << "Исходный список: ";
    list.PrintForward();
    list.SolveListWork46();
}