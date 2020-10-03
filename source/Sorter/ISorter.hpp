#pragma once

#include "../Sequence/Sequence.hpp"

template <class T>
class ISorter {
public:
    virtual Sequence<T>* Sort(Sequence<T>* sequence, int (*comparator)(T, T)) = 0;

protected:
    void Swap(Sequence<T>* sequence, int index1, int index2) {
        T item = sequence->Get(index1);
        sequence->Set(sequence->Get(index2), index1);
        sequence->Set(item, index2);
    }
};