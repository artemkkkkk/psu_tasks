#pragma once
#include "DynamicArray.h"
#include <stdexcept>

template<typename T>
class Stack {
private:
    DynamicArray<T> data;

public:
    Stack();
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    int getSize() const;
    bool isEmpty() const;
    void clear();
};

template<typename T>
Stack<T>::Stack() {}

template<typename T>
void Stack<T>::push(const T& value) {
    data.pushBack(value);
}

template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст");
    }
    data.popBack();
}

template<typename T>
T& Stack<T>::top() {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст");
    }
    return data.get(data.getSize() - 1);
}

template<typename T>
const T& Stack<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст");
    }
    return data.get(data.getSize() - 1);
}

template<typename T>
int Stack<T>::getSize() const {
    return data.getSize();
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return data.isEmpty();
}

template<typename T>
void Stack<T>::clear() {
    data.clear();
}