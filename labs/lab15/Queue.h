#pragma once
#include "DynamicArray.h"

template<typename T>
class Queue {
private:
    DynamicArray<T> data;

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