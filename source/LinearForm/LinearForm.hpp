#pragma once

#include <iostream>
#include "../Sequence/Sequence.hpp"
#include "../ArraySequence/ArraySequence.hpp"

using namespace std;

template <class T>
class LinearForm {
private:
    Sequence<T>* coefficients;
public:
    LinearForm(T* items, int size);

    LinearForm<T>& operator = (LinearForm<T> &other);

    LinearForm<T>& operator += (LinearForm<T> &other);

    T Get(int index);
};

template<class T>
LinearForm<T>::LinearForm(T* items, int size) {
    this->coefficients = new ArraySequence<T>(items, size);
}

template<class T>
LinearForm<T> &LinearForm<T>::operator=(LinearForm<T> &other) {
    Sequence<T> newCoef = ArraySequence<T>(other.coefficients);

    this->coefficients = newCoef;
}

template<class T>
LinearForm<T> &LinearForm<T>::operator+=(LinearForm<T> &other) {
    int size = this->coefficients->GetLength();
    T* newItems = new T[size];

    for (int i = 0; i < size; ++i) {
        newItems[i] = this->coefficients->Get(i) + other->coefficients->Get(i);
    }

    this->coefficients = new ArraySequence<T>(newItems, size);
    cout << newItems[0] << endl;

    return *this;
}

template<class T>
T LinearForm<T>::Get(int index) {
    this->coefficients->Get(index);
}

LinearForm<T>& operator *= (int val) {
    int size = this->coefficients->GetLength();
    T* newItems = new T[size];

    for (int i = 0; i < size; ++i) {
        newItems[i] = this->coefficients->Get(i) * val;
    }

    this->coefficients = new ArraySequence<T>(newItems, size);
    cout << newItems[0] << endl;

    return *this;
}
