#include "namering.h"
#include <iostream>
#include <fstream>

static bool namesEqual(const char* a, const char* b) {
    int i = 0;

    while (a[i] && b[i] && a[i] == b[i]) {
        ++i;
    }

    return a[i] == b[i];
}

void NameRing::clear() {
    if (!head) {
        return;
    }

    tail->Next = 0;
    NameNode* cur = head;

    while (cur) {
        NameNode* next = cur->Next;
        delete cur;
        cur = next;
    }

    head = 0;
    tail = 0;
    size = 0;
}

NameRing::NameRing() : head(0), tail(0), size(0) {}

NameRing::NameRing(const NameRing& other) : head(0), tail(0), size(0) {
    if (other.size == 0) {
        return;
    }

    NameNode* cur = other.head;

    for (int i = 0; i < other.size; ++i) {
        append(cur->Name);
        cur = cur->Next;
    }
}

NameRing::~NameRing() {
    clear();
}

NameRing& NameRing::operator=(const NameRing& other) {
    if (this != &other) {
        clear();

        if (other.size > 0) {
            NameNode* cur = other.head;

            for (int i = 0; i < other.size; ++i) {
                append(cur->Name);
                cur = cur->Next;
            }
        }
    }

    return *this;
}

bool NameRing::isEmpty() const {
    return size == 0;
}

int NameRing::count() const {
    return size;
}

bool NameRing::append(const char* name) {
    NameNode* node = new NameNode(name);

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
    return true;
}

bool NameRing::removeFirst(char* nameBuffer, int bufferSize) {
    if (!head) {
        return false;
    }

    if (nameBuffer && bufferSize > 0) {
        int i = 0;

        while (i < bufferSize - 1 && head->Name[i]) {
            nameBuffer[i] = head->Name[i];
            ++i;
        }

        nameBuffer[i] = '\0';
    }

    if (size == 1) {
        delete head;
        head = 0;
        tail = 0;
        size = 0;
        return true;
    }

    NameNode* newHead = head->Next;
    tail->Next = newHead;
    delete head;
    head = newHead;
    --size;

    return true;
}

NameNode* NameRing::findFirstName(const char* name) const {
    if (!head || !name) {
        return 0;
    }

    NameNode* cur = head;

    for (int i = 0; i < size; ++i) {
        if (namesEqual(cur->Name, name)) {
            return cur;
        }

        cur = cur->Next;
    }

    return 0;
}

void NameRing::print() const {
    if (!head) {
        std::cout << "Пусто\n";
        return;
    }

    NameNode* cur = head;

    for (int i = 0; i < size; ++i) {
        std::cout << cur->Name << '\n';
        cur = cur->Next;
    }
}

bool NameRing::eliminateWithStep(int step, const char* outputFile) {
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

    NameNode* prev = tail;
    NameNode* current = head;

    while (size > 0) {
        int moves = (step - 1) % size;

        for (int i = 0; i < moves; ++i) {
            prev = current;
            current = current->Next;
        }

        out << current->Name << '\n';
        std::cout << current->Name << '\n';

        NameNode* next = current->Next;

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

        current = prev->Next;
    }

    return true;
}