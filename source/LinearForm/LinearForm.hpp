#pragma once

#include <iostream>
#include "../Sequence/Sequence.hpp"
#include "../ArraySequence/ArraySequence.hpp"
#include "../ListSequence/ListSequence.hpp"

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

    LinearForm<T> &operator*=(const T value);

    LinearForm<T> operator*(const T value);

    T eval(T *values, int size);

    template<class M>
    friend ostream &operator << (ostream &os, const LinearForm<M> &lf);

    T Get(int index);

    int GetLength();
};

template<class T>
LinearForm<T>::LinearForm() {
    //this->coefficients = new ArrySequence<T>(1);
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
LinearForm<T> &LinearForm<T>::operator*=(const T value) {
    int size = this->coefficients->GetLength();

    for (int i = 0; i < size; ++i) {
        this->coefficients->Set(this->coefficients->Get(i) * value, i);
    }

    return *this;
}

template<class T>
LinearForm<T> LinearForm<T>::operator*(const T value) {
    LinearForm<T> result = *this;
    result *= value;

    return result;
}


template<class T>
LinearForm<T> &LinearForm<T>::operator-=(const LinearForm<T> &other) {
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
        this->coefficients->Set(this->coefficients->Get(i) - other.coefficients->Get(i), i);
    }

    for (int i = size_min; i < size_max; ++i) {
        if (size1 < size2) {
            this->coefficients->Append(-other.coefficients->Get(i));
        }
    }

    return *this;
}

template<class T>
LinearForm<T> LinearForm<T>::operator-(const LinearForm<T> &other) {
    LinearForm<T> result = *this;
    result -= other;

    return result;
}

template<class T>
T LinearForm<T>::eval(T *values, int size) {
    int thisLen = this->coefficients->GetLength();
    if (size != thisLen - 1) {
        throw new Exception;
    }

    T result = this->coefficients->Get(0);

    for (int i = 1; i < thisLen; ++i) {
        result += this->coefficients->Get(i) * values[i - 1];
    }

    return result;
}

template<class M>
ostream &operator<<(ostream &os, const LinearForm<M> &lf) {
    if (lf.coefficients->GetLength() < 1) {
        throw new Exception;
    }

    os << "c = " << lf.coefficients->Get(0);
    for (int i = 1; i < lf.coefficients->GetLength(); ++i) {
        os << ", x" << i << " = " << lf.coefficients->Get(i);
    }

    return os;
}

template<class T>
int LinearForm<T>::GetLength() {
    return this->coefficients->GetLength();
}


