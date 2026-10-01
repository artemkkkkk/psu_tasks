#include "doublylist.h"
#include <iostream>

void DoublyList::clear() {
    TNode2* cur = head;

    while (cur) {
        TNode2* next = cur->Next;
        delete cur;
        cur = next;
    }

    head = 0;
    tail = 0;
    size = 0;
}

DoublyList::DoublyList() : head(0), tail(0), size(0) {}

DoublyList::DoublyList(const DoublyList& other) : head(0), tail(0), size(0) {
    TNode2* cur = other.head;

    while (cur) {
        pushBack(cur->Data);
        cur = cur->Next;
    }
}

DoublyList::~DoublyList() {
    clear();
}

DoublyList& DoublyList::operator=(const DoublyList& other) {
    if (this != &other) {
        clear();

        TNode2* cur = other.head;
        while (cur) {
            pushBack(cur->Data);
            cur = cur->Next;
        }
    }

    return *this;
}

bool DoublyList::isEmpty() const {
    return size == 0;
}

int DoublyList::count() const {
    return size;
}

void DoublyList::pushBack(int value) {
    TNode2* node = new TNode2(value);

    if (!head) {
        head = node;
        tail = node;
    } else {
        tail->Next = node;
        node->Prev = tail;
        tail = node;
    }

    ++size;
}

bool DoublyList::removeFirst(int& value) {
    if (!head) {
        return false;
    }

    value = head->Data;
    TNode2* old = head;
    head = head->Next;

    if (head) {
        head->Prev = 0;
    } else {
        tail = 0;
    }

    delete old;
    --size;

    return true;
}

TNode2* DoublyList::findFirstValue(int value) const {
    TNode2* cur = head;

    while (cur) {
        if (cur->Data == value) {
            return cur;
        }

        cur = cur->Next;
    }

    return 0;
}

TNode2* DoublyList::headNode() const {
    return head;
}

TNode2* DoublyList::tailNode() const {
    return tail;
}

void DoublyList::release() {
    head = 0;
    tail = 0;
    size = 0;
}

TNode2* DoublyList::moveOddPositionsToEnd() {
    if (size == 0) {
        return 0;
    }

    TNode2* oddHead = 0;
    TNode2* oddTail = 0;
    TNode2* evenHead = 0;
    TNode2* evenTail = 0;

    TNode2* cur = head;
    int pos = 1;

    while (cur) {
        TNode2* next = cur->Next;

        cur->Next = 0;
        cur->Prev = 0;

        if (pos % 2 == 1) {
            if (!oddHead) {
                oddHead = cur;
                oddTail = cur;
            } else {
                oddTail->Next = cur;
                cur->Prev = oddTail;
                oddTail = cur;
            }
        } else {
            if (!evenHead) {
                evenHead = cur;
                evenTail = cur;
            } else {
                evenTail->Next = cur;
                cur->Prev = evenTail;
                evenTail = cur;
            }
        }

        cur = next;
        ++pos;
    }

    if (evenHead) {
        head = evenHead;
        evenTail->Next = oddHead;

        if (oddHead) {
            oddHead->Prev = evenTail;
        }

        tail = oddTail ? oddTail : evenTail;
    } else {
        head = oddHead;
        tail = oddTail;
    }

    return head;
}

void DoublyList::print() const {
    if (!head) {
        std::cout << "Пусто\n";
        return;
    }

    TNode2* cur = head;

    while (cur) {
        std::cout << cur->Data << ' ';
        cur = cur->Next;
    }

    std::cout << '\n';
}