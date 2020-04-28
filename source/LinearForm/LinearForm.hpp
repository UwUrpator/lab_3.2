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

    LinearForm<T> &operator+=(const LinearForm<T> &other);

    LinearForm<T> operator+(const LinearForm<T> &other);

    LinearForm<T> &operator-=(const LinearForm<T> &other);

    LinearForm<T> operator-(const LinearForm<T> &other);

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
LinearForm<T> &LinearForm<T>::operator+=(const LinearForm<T> &other) {
    int size1 = this->coefficients->GetLength();
    int size2 = other.coefficients->GetLength();

    int size_max = 0;
    int size_min = 0;

    if (size1 >= size2) {
        size_max = size1;
        size_min = size2;
    } else {
        size_max = size2;
        size_min = size1;
    }

    for (int i = 0; i < size_min; ++i) {
        this->coefficients->Set(this->coefficients->Get(i) + other.coefficients->Get(i), i);
    }

    for (int i = size_min; i < size_max; ++i) {
        if (size1 < size2) {
            this->coefficients->Append(other.coefficients->Get(i));
        }
    }

    return *this;
}

template<class T>
LinearForm<T> LinearForm<T>::operator+(const LinearForm<T> &other) {
    LinearForm<T> result = *this;
    result += other;

    return result;
}

template<class T>
T LinearForm<T>::Get(int index) {
    return this->coefficients->Get(index);
}

template<class T>
LinearForm<T> &LinearForm<T>::operator*=(const int value) {
    int size = this->coefficients->GetLength();

    for (int i = 0; i < size; ++i) {
        this->coefficients->Set(this->coefficients->Get(i) * value, i);
    }

    return *this;
}



