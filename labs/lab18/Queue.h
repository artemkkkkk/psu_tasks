#pragma once
#include "DynamicArray.h"
#include <stdexcept>

template<typename T>
class Queue {
private:
    DynamicArray<T> data;
    int frontIndex;

public:
    Queue();
    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    int getSize() const;
    bool isEmpty() const;
    void clear();
};

template<typename T>
Queue<T>::Queue() : frontIndex(0) {}

template<typename T>
void Queue<T>::push(const T& value) {
    data.pushBack(value);
}

template<typename T>
void Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }
    frontIndex++;
}

template<typename T>
T& Queue<T>::front() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }
    return data.get(frontIndex);
}

template<typename T>
const T& Queue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }
    return data.get(frontIndex);
}

template<typename T>
int Queue<T>::getSize() const {
    return data.getSize() - frontIndex;
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return frontIndex >= data.getSize();
}

template<typename T>
void Queue<T>::clear() {
    data.clear();
    frontIndex = 0;
}