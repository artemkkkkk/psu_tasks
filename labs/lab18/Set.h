#pragma once
#include "DynamicArray.h"

template<typename T>
class Set {
private:
    DynamicArray<T> data;

public:
    Set();
    void insert(const T& value);
    bool contains(const T& value) const;
    int getSize() const;
    bool isEmpty() const;
    void clear();
    const T& getAt(int index) const;
};

template<typename T>
Set<T>::Set() {}

template<typename T>
void Set<T>::insert(const T& value) {
    if (!contains(value)) {
        data.pushBack(value);
    }
}

template<typename T>
bool Set<T>::contains(const T& value) const {
    for (int i = 0; i < data.getSize(); ++i) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
int Set<T>::getSize() const {
    return data.getSize();
}

template<typename T>
bool Set<T>::isEmpty() const {
    return data.isEmpty();
}

template<typename T>
void Set<T>::clear() {
    data.clear();
}

template<typename T>
const T& Set<T>::getAt(int index) const {
    return data[index];
}