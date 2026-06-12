#ifndef STACK_H
#define STACK_H

#include <string>
#include "exceptions.h"

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    size_t stackSize;

public:
    Stack() : topNode(nullptr), stackSize(0) {}

    ~Stack() {
        clear();
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    bool isEmpty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        return stackSize;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        stackSize++;
    }

    T pop() {
        if (isEmpty()) {
            throw StackException("Stack underflow: попытка извлечения из пустого стека");
        }

        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        stackSize--;

        return value;
    }

    T& top() {
        if (isEmpty()) {
            throw StackException("Stack is empty: попытка доступа к вершине пустого стека");
        }
        return topNode->data;
    }

    const T& top() const {
        if (isEmpty()) {
            throw StackException("Stack is empty: попытка доступа к вершине пустого стека");
        }
        return topNode->data;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif // STACK_H