#pragma once
#include <stdexcept>

template<typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void resize(int newCapacity);

public:
    DynamicArray();
    DynamicArray(int initialCapacity);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);

    void pushBack(const T& value);
    void popBack();
    T& get(int index);
    const T& get(int index) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;
    void clear();
    void remove(int index);
    T* getData();
    const T* getData() const;
};

template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}

template<typename T>
DynamicArray<T>::DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
    if (initialCapacity > 0) {
        data = new T[initialCapacity];
    } else {
        data = nullptr;
        capacity = 0;
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
    if (capacity > 0) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr;
    }
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        if (capacity > 0) {
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    return *this;
}

template<typename T>
void DynamicArray<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
void DynamicArray<T>::pushBack(const T& value) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size++] = value;
}

template<typename T>
void DynamicArray<T>::popBack() {
    if (size > 0) {
        size--;
    }
}

template<typename T>
T& DynamicArray<T>::get(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[index];
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {
    return get(index);
}

template<typename T>
const T& DynamicArray<T>::operator[](int index) const {
    return get(index);
}

template<typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template<typename T>
int DynamicArray<T>::getCapacity() const {
    return capacity;
}

template<typename T>
bool DynamicArray<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void DynamicArray<T>::clear() {
    size = 0;
}

template<typename T>
void DynamicArray<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
T* DynamicArray<T>::getData() {
    return data;
}

template<typename T>
const T* DynamicArray<T>::getData() const {
    return data;
}