#include "cyclicdoublylist.h"
#include <iostream>

void CyclicDoublyList::clear() {
    if (!first) {
        return;
    }

    TNode2* last = first->Prev;
    last->Next = 0;

    TNode2* cur = first;

    while (cur) {
        TNode2* next = cur->Next;
        delete cur;
        cur = next;
    }

    first = 0;
    size = 0;
}

void CyclicDoublyList::removeNode(TNode2* node) {
    if (!node || size == 0) {
        return;
    }

    if (size == 1) {
        delete node;
        first = 0;
        size = 0;
        return;
    }

    TNode2* prev = node->Prev;
    TNode2* next = node->Next;

    prev->Next = next;
    next->Prev = prev;

    if (node == first) {
        first = next;
    }

    delete node;
    --size;
}

CyclicDoublyList::CyclicDoublyList() : first(0), size(0) {}

CyclicDoublyList::CyclicDoublyList(const CyclicDoublyList& other) : first(0), size(0) {
    if (other.size == 0) {
        return;
    }

    TNode2* cur = other.first;

    for (int i = 0; i < other.size; ++i) {
        append(cur->Data);
        cur = cur->Next;
    }
}

CyclicDoublyList::~CyclicDoublyList() {
    clear();
}

CyclicDoublyList& CyclicDoublyList::operator=(const CyclicDoublyList& other) {
    if (this != &other) {
        clear();

        if (other.size > 0) {
            TNode2* cur = other.first;

            for (int i = 0; i < other.size; ++i) {
                append(cur->Data);
                cur = cur->Next;
            }
        }
    }

    return *this;
}

bool CyclicDoublyList::isEmpty() const {
    return size == 0;
}

int CyclicDoublyList::count() const {
    return size;
}

void CyclicDoublyList::append(int value) {
    TNode2* node = new TNode2(value);

    if (!first) {
        first = node;
        node->Next = node;
        node->Prev = node;
    } else {
        TNode2* last = first->Prev;

        last->Next = node;
        node->Prev = last;
        node->Next = first;
        first->Prev = node;
    }

    ++size;
}

bool CyclicDoublyList::removeFirst(int& value) {
    if (!first) {
        return false;
    }

    value = first->Data;
    TNode2* node = first;
    removeNode(node);

    return true;
}

TNode2* CyclicDoublyList::findFirstValue(int value) const {
    if (!first) {
        return 0;
    }

    TNode2* cur = first;

    for (int i = 0; i < size; ++i) {
        if (cur->Data == value) {
            return cur;
        }

        cur = cur->Next;
    }

    return 0;
}

TNode2* CyclicDoublyList::firstNode() const {
    return first;
}

TNode2* CyclicDoublyList::lastNode() const {
    if (!first) {
        return 0;
    }

    return first->Prev;
}

int CyclicDoublyList::removeEqualNeighborValues() {
    if (size == 0) {
        return 0;
    }

    int originalSize = size;
    int deleteCount = 0;

    TNode2* cur = first;

    for (int i = 0; i < originalSize; ++i) {
        if (cur->Prev->Data == cur->Next->Data) {
            ++deleteCount;
        }

        cur = cur->Next;
    }

    if (deleteCount == 0) {
        return 0;
    }

    TNode2** nodesToDelete = new TNode2*[deleteCount];

    cur = first;
    int idx = 0;

    for (int i = 0; i < originalSize; ++i) {
        if (cur->Prev->Data == cur->Next->Data) {
            nodesToDelete[idx++] = cur;
        }

        cur = cur->Next;
    }

    for (int i = 0; i < deleteCount; ++i) {
        removeNode(nodesToDelete[i]);
    }

    delete[] nodesToDelete;

    return deleteCount;
}

void CyclicDoublyList::print() const {
    if (!first) {
        std::cout << "Пусто\n";
        return;
    }

    TNode2* cur = first;

    for (int i = 0; i < size; ++i) {
        std::cout << cur->Data << ' ';
        cur = cur->Next;
    }

    std::cout << '\n';
}