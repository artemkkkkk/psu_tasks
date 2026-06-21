#pragma once
#include "DynamicArray.h"
#include <stdexcept>

template<typename T>
class PriorityQueue {
private:
    DynamicArray<T> data;
    int (*comparator)(const T&, const T&);

public:
    PriorityQueue(int (*cmp)(const T&, const T&));
    void push(const T& value);
    T& top();
    const T& top() const;
    void pop();
    int getSize() const;
    bool isEmpty() const;
    void clear();
};

template<typename T>
PriorityQueue<T>::PriorityQueue(int (*cmp)(const T&, const T&)) : comparator(cmp) {}

template<typename T>
void PriorityQueue<T>::push(const T& value) {
    data.pushBack(value);
}

template<typename T>
T& PriorityQueue<T>::top() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }
    int minIndex = 0;
    for (int i = 1; i < data.getSize(); ++i) {
        if (comparator(data[i], data[minIndex]) < 0) {
            minIndex = i;
        }
    }
    return data[minIndex];
}

template<typename T>
const T& PriorityQueue<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }
    int minIndex = 0;
    for (int i = 1; i < data.getSize(); ++i) {
        if (comparator(data[i], data[minIndex]) < 0) {
            minIndex = i;
        }
    }
    return data[minIndex];
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста");
    }
    int minIndex = 0;
    for (int i = 1; i < data.getSize(); ++i) {
        if (comparator(data[i], data[minIndex]) < 0) {
            minIndex = i;
        }
    }
    data.remove(minIndex);
}

template<typename T>
int PriorityQueue<T>::getSize() const {
    return data.getSize();
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const {
    return data.isEmpty();
}

template<typename T>
void PriorityQueue<T>::clear() {
    data.clear();
}