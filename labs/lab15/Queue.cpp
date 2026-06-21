#include "Queue.h"

template<typename T>
Queue<T>::Queue() {}

template<typename T>
void Queue<T>::push(const T& value) {
    data.pushBack(value);
}

template<typename T>
void Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    data.remove(0);
}

template<typename T>
T& Queue<T>::front() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data.get(0);
}

template<typename T>
const T& Queue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data.get(0);
}

template<typename T>
int Queue<T>::getSize() const {
    return data.getSize();
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return data.isEmpty();
}

template<typename T>
void Queue<T>::clear() {
    data.clear();
}

template class Queue<int>;
template class Queue<double>;
template class Queue<char>;