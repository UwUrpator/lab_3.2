#pragma once

#include "../Sorter/ISorter.hpp"
#include "../Sequence/Sequence.hpp"

template<class T>
class ShellSorter : ISorter<T> {
public:
    virtual Sequence<T>* Sort(Sequence<T>* sequence, int (*comparator)(T, T)) override;

private:
    Sequence<T>* Sort(Sequence<T>* sequence, int (*comparator)(T, T), int size);
};

template<class T>
Sequence<T>* ShellSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)) {
    return this->Sort(sequence, comparator, sequence->GetLength());
}

template<class T>
Sequence<T> *ShellSorter<T>::Sort(Sequence<T> *sequence, int (*comparator)(T, T), int size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = step; i < size; i++) {
            for (int j = i - step; j >= 0 && comparator(sequence->Get(j), sequence->Get(j + step)) > 0; j -= step) {
                this->Swap(sequence, j, j + step);
            }
        }
    }

    return sequence;
}
