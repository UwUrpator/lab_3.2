#pragma once

#include <iostream>
#include "Sequence.hpp"
#include "ArraySequence.hpp"

using namespace std;

template <class T>
class LinearForm {
private:
    Sequence<T>* coefficients;
public:
    LinearForm(T* items, int size) {
        this->coefficients = new ArraySequence<T>(items, size);
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

    LinearForm<T>& operator = (LinearForm<T> &other) {
        Sequence<T> newCoef = ArraySequence<T>(other.coefficients);

        this->coefficients = newCoef;
    }

    LinearForm<T>& operator += (LinearForm<T> &other) {
        int size = this->coefficients->GetLength();
        T* newItems = new T[size];

        for (int i = 0; i < size; ++i) {
            newItems[i] = this->coefficients->Get(i) + other->coefficients->Get(i);
        }

        this->coefficients = new ArraySequence<T>(newItems, size);
        cout << newItems[0] << endl;

        return *this;
    }

    T Get(int index) {
        this->coefficients->Get(index);
    }
};