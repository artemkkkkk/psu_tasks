#include "list.h"
#include <iostream>

void List::clear() {
    while (head) {
        TNode* old = head;
        head = head->Next;
        delete old;
    }

    tail = 0;
    size = 0;
}

List::List() : head(0), tail(0), size(0) {}

List::List(const List& other) : head(0), tail(0), size(0) {
    TNode* cur = other.head;

    while (cur) {
        pushBack(cur->Data);
        cur = cur->Next;
    }
}

List::~List() {
    clear();
}

List& List::operator=(const List& other) {
    if (this != &other) {
        clear();

        TNode* cur = other.head;
        while (cur) {
            pushBack(cur->Data);
            cur = cur->Next;
        }
    }

    return *this;
}

bool List::isEmpty() const {
    return head == 0;
}

int List::count() const {
    return size;
}

void List::pushBack(int value) {
    TNode* node = new TNode(value);

    if (!head) {
        head = node;
        tail = node;
    } else {
        tail->Next = node;
        tail = node;
    }

    ++size;
}

bool List::removeFirst(int& value) {
    if (!head) {
        return false;
    }

    value = head->Data;
    TNode* old = head;
    head = head->Next;

    if (!head) {
        tail = 0;
    }

    delete old;
    --size;

    return true;
}

TNode* List::findFirstValue(int value) const {
    TNode* cur = head;

    while (cur) {
        if (cur->Data == value) {
            return cur;
        }

        cur = cur->Next;
    }

    return 0;
}

TNode* List::at(int index) const {
    if (index < 1) {
        return 0;
    }

    TNode* cur = head;
    int pos = 1;

    while (cur && pos < index) {
        cur = cur->Next;
        ++pos;
    }

    return cur;
}

TNode* List::lastNode() const {
    return tail;
}

void List::insertAfterEveryK(int k, int value) {
    if (k <= 0 || !head) {
        return;
    }

    TNode* cur = head;
    int pos = 1;

    while (cur) {
        TNode* next = cur->Next;

        if (pos % k == 0) {
            TNode* node = new TNode(value);
            node->Next = next;
            cur->Next = node;

            if (cur == tail) {
                tail = node;
            }

            ++size;
        }

        cur = next;
        ++pos;
    }
}

void List::print() const {
    TNode* cur = head;

    while (cur) {
        std::cout << cur->Data << ' ';
        cur = cur->Next;
    }

    std::cout << '\n';
}