#include "ring.h"
#include <iostream>
#include <fstream>

void Ring::clear() {
    if (!head) {
        return;
    }

    tail->Next = 0;
    TNode* cur = head;

    while (cur) {
        TNode* next = cur->Next;
        delete cur;
        cur = next;
    }

    head = 0;
    tail = 0;
    size = 0;
}

Ring::Ring() : head(0), tail(0), size(0) {}

Ring::Ring(const Ring& other) : head(0), tail(0), size(0) {
    if (other.size == 0) {
        return;
    }

    TNode* cur = other.head;

    for (int i = 0; i < other.size; ++i) {
        append(cur->Data);
        cur = cur->Next;
    }
}

Ring::~Ring() {
    clear();
}

Ring& Ring::operator=(const Ring& other) {
    if (this != &other) {
        clear();

        if (other.size > 0) {
            TNode* cur = other.head;

            for (int i = 0; i < other.size; ++i) {
                append(cur->Data);
                cur = cur->Next;
            }
        }
    }

    return *this;
}

bool Ring::isEmpty() const {
    return size == 0;
}

int Ring::count() const {
    return size;
}

void Ring::append(int value) {
    TNode* node = new TNode(value);

    if (!head) {
        head = node;
        tail = node;
        node->Next = head;
    } else {
        tail->Next = node;
        node->Next = head;
        tail = node;
    }

    ++size;
}

bool Ring::removeFirst(int& value) {
    if (!head) {
        return false;
    }

    value = head->Data;

    if (size == 1) {
        delete head;
        head = 0;
        tail = 0;
        size = 0;
        return true;
    }

    TNode* newHead = head->Next;
    tail->Next = newHead;
    delete head;
    head = newHead;
    --size;

    return true;
}

TNode* Ring::findFirstValue(int value) const {
    if (!head) {
        return 0;
    }

    TNode* cur = head;

    for (int i = 0; i < size; ++i) {
        if (cur->Data == value) {
            return cur;
        }

        cur = cur->Next;
    }

    return 0;
}

void Ring::print() const {
    if (!head) {
        std::cout << "Пусто\n";
        return;
    }

    TNode* cur = head;

    for (int i = 0; i < size; ++i) {
        std::cout << cur->Data << ' ';
        cur = cur->Next;
    }

    std::cout << '\n';
}

bool Ring::eliminateWithStep(int step, const char* outputFile) {
    if (step <= 0 || !outputFile) {
        return false;
    }

    std::ofstream out(outputFile);
    if (!out) {
        return false;
    }

    if (size == 0) {
        return true;
    }

    TNode* prev = tail;
    TNode* current = head;
    bool firstWritten = false;

    while (size > 0) {
        if (firstWritten) {
            out << ' ';
            std::cout << ' ';
        }

        out << current->Data;
        std::cout << current->Data;
        firstWritten = true;

        TNode* next = current->Next;

        if (size == 1) {
            delete current;
            head = 0;
            tail = 0;
            size = 0;
            break;
        }

        if (current == head) {
            head = next;
        }

        if (current == tail) {
            tail = prev;
        }

        prev->Next = next;
        delete current;
        --size;

        current = next;

        int moves = (step - 1) % size;
        for (int i = 0; i < moves; ++i) {
            prev = current;
            current = current->Next;
        }
    }

    out << '\n';
    std::cout << '\n';

    return true;
}