#include "queue.h"
#include <iostream>

void Queue::clear() {
    while (head) {
        TNode* old = head;
        head = head->Next;
        delete old;
    }

    tail = 0;
    size = 0;
}

Queue::Queue() : head(0), tail(0), size(0) {}

Queue::Queue(const Queue& other) : head(0), tail(0), size(0) {
    TNode* cur = other.head;

    while (cur) {
        pushBack(cur->Data);
        cur = cur->Next;
    }
}

Queue::~Queue() {
    clear();
}

Queue& Queue::operator=(const Queue& other) {
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

bool Queue::isEmpty() const {
    return head == 0;
}

int Queue::count() const {
    return size;
}

void Queue::pushBack(int value) {
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

bool Queue::popFront(int& value) {
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

TNode* Queue::headNode() const {
    return head;
}

TNode* Queue::tailNode() const {
    return tail;
}

void Queue::release() {
    head = 0;
    tail = 0;
    size = 0;
}

void Queue::adopt(TNode* newHead, TNode* newTail, int newSize) {
    head = newHead;
    tail = newTail;
    size = newSize;
}

void Queue::print() const {
    TNode* cur = head;

    while (cur) {
        std::cout << cur->Data << ' ';
        cur = cur->Next;
    }

    std::cout << '\n';
}