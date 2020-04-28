#pragma once

#include <iostream>
#include "../Sequence/Sequence.hpp"
#include "../ArraySequence/ArraySequence.hpp"

using namespace std;

template<class T>
class LinearForm {
private:
    Sequence<T> *coefficients;
public:
    LinearForm();

    LinearForm(T *items, int size);

    LinearForm<T> &operator=(const LinearForm<T> &other);

    LinearForm<T> &operator+=(LinearForm<T> &other);

    LinearForm<T> &operator*=(const int value);

    T Get(int index);
};

template<class T>
LinearForm<T>::LinearForm() {
    this->coefficients = new ArraySequence<T>(1);
}

template<class T>
LinearForm<T>::LinearForm(T *items, int size) {
    this->coefficients = new ArraySequence<T>(items, size);
}

template<class T>
LinearForm<T> &LinearForm<T>::operator=(const LinearForm<T> &other) {
    Sequence<T> *newCoef = other.coefficients->Copy();
    this->coefficients = newCoef;

    return *this;
}

template<class T>
LinearForm<T> &LinearForm<T>::operator+=(LinearForm<T> &other) {
    int size = this->coefficients->GetLength();
    T *newItems = new T[size];

    for (int i = 0; i < size; ++i) {
        newItems[i] = this->coefficients->Get(i) + other->coefficients->Get(i);
    }

    this->coefficients = new ArraySequence<T>(newItems, size);
    cout << newItems[0] << endl;

    return *this;
}

template<class T>
T LinearForm<T>::Get(int index) {
    return this->coefficients->Get(index);
}

template<class T>
LinearForm<T> &LinearForm<T>::operator*=(const int value) {
    int size = this->coefficients->GetLength();
    T *newItems = new T[size];

    for (int i = 0; i < size; ++i) {
        newItems[i] = this->coefficients->Get(i) * value;
    }

    this->coefficients = new ArraySequence<T>(newItems, size);
    cout << newItems[0] << endl;

    return *this;
}



