#pragma once

#include <iostream>
#include "../../Exception.hpp"
#include "Optional.hpp"

template<class T>
class DynamicArray {
private:
    Optional<T> *items;
    int size;

public:
    DynamicArray(T *items, int size);

    DynamicArray(const int size);

    DynamicArray(const DynamicArray<T> &array);

    DynamicArray<T> &operator=(const DynamicArray &array);

    Optional<T> &operator[](int index);

    int GetSize() const;

    T Get(const int index) const;

    void Set(const int index, const T value);

    void Resize(int newSize);
};

template<class T>
DynamicArray<T>::DynamicArray(T *items, int size) {
    if (size < 1) {
        throw new Exception;
    }
    this->items = static_cast<Optional<T> *>(operator new[](size * sizeof(Optional<T>)));
    this->size = size;
    for (int i = 0; i < size; ++i) {
        this->items[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(const int size) {
    if (size < 1) {
        throw new Exception;
    }
    this->items = static_cast<Optional<T> *>(operator new[](size * sizeof(Optional<T>)));
    for (int i = 0; i < size; i++)
        this->items[i] = *Optional<T>::Empty();
    this->size = size;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &array) {
    (*this) = array;
}

template<class T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &array) {
    this->size = array.size;
    this->items = static_cast<Optional<T> *>(operator new[](size * sizeof(Optional<T>)));
    for (int i = 0; i < this->size; ++i) {
        this->items[i] = array.items[i];
    }
    return *this;
}

template<class T>
Optional<T> &DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= this->size) {
        throw new Exception;
    }
    return this->items[index];
}

template<class T>
int DynamicArray<T>::GetSize() const {
    return this->size;
}

template<class T>
T DynamicArray<T>::Get(const int index) const {
    if (index < 0 || index >= this->size || !this->items[index].HasValue())
        throw new Exception;
    return this->items[index].GetValue();
}

template<class T>
void DynamicArray<T>::Set(const int index, const T value) {
    if (index < 0 || index >= this->size)
        throw new Exception;
    this->items[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 1) {
        throw new Exception;
    }
    if (newSize <= this->size) {
        for (int i = newSize; i < this->size; ++i) {
            this->items[i].~Optional();
        }
    } else if (newSize > this->size) {
        Optional<T> *newItems = static_cast<Optional<T> *>(operator new[](size * sizeof(Optional<T>)));
        for (int i = 0; i < this->size; ++i) {
            newItems[i] = this->items[i];
        }
        for (int i = this->size; i < newSize; ++i) {
            newItems[i] = *Optional<T>::Empty();
        }
        this->items = newItems;
    }

    this->size = newSize;
}
