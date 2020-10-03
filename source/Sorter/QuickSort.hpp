#pragma once

#include "../Sorter/ISorter.hpp"
#include "../Sequence/Sequence.hpp"

template<class T>
class QuickSort : ISorter<T> {
public:
    virtual Sequence<T>* Sort(Sequence<T>* sequence, int (*comparator)(T, T)) override;

private:
    Sequence<T>* Sort(Sequence<T>* sequence, int (*comparator)(T, T), int left, int right);
};

template<class T>
Sequence<T>* QuickSort<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)) {
    return this->Sort(sequence, comparator, 0, sequence->GetLength() - 1);
}

template<class T>
Sequence<T> *QuickSort<T>::Sort(Sequence<T> *sequence, int (*comparator)(T, T), int left, int right) {
    int l = left;
    int r = right;

    T pivot = sequence->Get((l + r) / 2);

    while (l <= r) {
        while (comparator(sequence->Get(l), pivot) < 0)
            l++;

        while (comparator(sequence->Get(r), pivot) > 0)
            r--;

        if (l <= r) {
            this->Swap(sequence, l, r);
            l++;
            r--;
        }
    }

    if (r > left)
        this->Sort(sequence, comparator, left, r);

    if (l < right)
        this->Sort(sequence, comparator, l, right);

    return sequence;
}
