#pragma once
#include "DynamicArray.h"
#include <stdexcept>

template<typename K, typename V>
class Map {
private:
    struct Entry {
        K key;
        V value;
        Entry() : key(), value() {}
        Entry(const K& k, const V& v) : key(k), value(v) {}
    };
    DynamicArray<Entry> entries;

public:
    Map();
    void put(const K& key, const V& value);
    V& get(const K& key);
    const V& get(const K& key) const;
    bool contains(const K& key) const;
    int getSize() const;
    bool isEmpty() const;
    void clear();
    const K& getKeyAt(int index) const;
    const V& getValueAt(int index) const;
};

template<typename K, typename V>
Map<K, V>::Map() {}

template<typename K, typename V>
void Map<K, V>::put(const K& key, const V& value) {
    for (int i = 0; i < entries.getSize(); ++i) {
        if (entries[i].key == key) {
            entries[i].value = value;
            return;
        }
    }
    entries.pushBack(Entry(key, value));
}

template<typename K, typename V>
V& Map<K, V>::get(const K& key) {
    for (int i = 0; i < entries.getSize(); ++i) {
        if (entries[i].key == key) {
            return entries[i].value;
        }
    }
    throw std::out_of_range("Ключ не найден");
}

template<typename K, typename V>
const V& Map<K, V>::get(const K& key) const {
    for (int i = 0; i < entries.getSize(); ++i) {
        if (entries[i].key == key) {
            return entries[i].value;
        }
    }
    throw std::out_of_range("Ключ не найден");
}

template<typename K, typename V>
bool Map<K, V>::contains(const K& key) const {
    for (int i = 0; i < entries.getSize(); ++i) {
        if (entries[i].key == key) {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
int Map<K, V>::getSize() const {
    return entries.getSize();
}

template<typename K, typename V>
bool Map<K, V>::isEmpty() const {
    return entries.isEmpty();
}

template<typename K, typename V>
void Map<K, V>::clear() {
    entries.clear();
}

template<typename K, typename V>
const K& Map<K, V>::getKeyAt(int index) const {
    return entries[index].key;
}

template<typename K, typename V>
const V& Map<K, V>::getValueAt(int index) const {
    return entries[index].value;
}