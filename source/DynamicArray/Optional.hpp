#pragma once

#include "../../Exception.hpp"
#include <iostream>

template<class T>
class Optional {
private:
    static Optional<T> *empty;
    static bool emptyIsSet;
    T value;
    bool hasValue;

public:
    static Optional<T>* Empty();

    Optional(T value);

    T GetValue() const;

    bool HasValue() const;

    bool TryGetValue(T &value) const;

    bool operator==(Optional<T> &other);

    operator T() const;

    T& operator=(const T& other);

//private:
    Optional();
};

template<class T>
Optional<T> *Optional<T>::Empty() {
    if (!emptyIsSet) {
        empty = new Optional<T>();
        emptyIsSet = true;
    }

    return empty;
}

template<class T>
Optional<T>::Optional(T value) {
    this->value = value;
    this->hasValue = true;
}

template<class T>
T Optional<T>::GetValue() const {
    if (this->hasValue)
        return this->value;
    else
        throw new Exception; // Invalid Operation Exception
}

template<class T>
bool Optional<T>::HasValue() const {
    return this->hasValue;
}

template<class T>
bool Optional<T>::TryGetValue(T &value) const {
    if (!this->hasValue)
        return false;
    value = this->value;
    return true;
}

template<class T>
bool Optional<T>::operator==(Optional<T> &other) {
    return this->hasValue == other.hasValue && (!this->hasValue || this->value == other.value);
}

template<class T>
Optional<T>::operator T() const {
    if (!this->hasValue) {
        throw new Exception;
    }
    return this->value;
}

template<class T>
Optional<T>::Optional() {
    this->hasValue = false;
}

template<class T>
T &Optional<T>::operator=(const T &other) {
    this->value = other;
    this->hasValue = true;
    return this->value;
}

template<class T>
bool Optional<T>::emptyIsSet;

template<class T>
Optional<T>* Optional<T>::empty;
