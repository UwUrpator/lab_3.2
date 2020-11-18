#pragma once

#include "../Sequence/Sequence.hpp"
#include "../DynamicArray/DynamicArray.hpp"

#include <iostream>
using namespace std;

template<class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> *items;
    int count;
public:
    ArraySequence(const int count);

    ArraySequence(T *items, int count);

    ArraySequence(const Sequence<T> &other);

    ArraySequence(const DynamicArray<T> *other);

    ArraySequence(const ArraySequence<T> &other);

    virtual int GetLength() const override;

    virtual T GetFirst() const override;

    virtual T GetLast() const override;

    virtual T Get(const int index) const override;

    virtual Sequence<T> *GetSubsequence(const int start_index, const int end_index) const override;

    virtual void Prepend(T value) override;

    virtual void Append(T value) override;

    virtual void InsertAt(T value, const int index) override;

    virtual void RemoveAt(const int index) override;

    virtual void Remove(T value) override;

    virtual void Remove(bool (*checker)(T item));

    virtual void RemoveAll(T value) override;

    virtual void RemoveAll(bool (*checker)(T item));

    virtual Sequence<T> *Concat(Sequence<T> *other) override;

    virtual Sequence<T> *Copy() override;

    virtual void Set(T value, const int index) override;
};

template<class T>
ArraySequence<T>::ArraySequence(const int count) {
    this->items = new DynamicArray<T>(count);
    this->count = count;
}

template<class T>
ArraySequence<T>::ArraySequence(T *items, int count) {
    this->items = new DynamicArray<T>(items, count);
    this->count = count;
}

template<class T>
ArraySequence<T>::ArraySequence(const Sequence<T> &other) {
    const ArraySequence<T> *castedArray = static_cast<const ArraySequence<T> *>(&other);

    if (castedArray) {
        this->items = new DynamicArray<T>(*castedArray->items);
        this->count = castedArray->GetLength();

        return;
    }

    int newLength = other.GetLength();
    DynamicArray<T> *newArray = new DynamicArray<T>(newLength);
    for (int i = 0; i < newLength; ++i) {
        (*newArray)[i] = other.Get(i);
    }
    this->items = newArray;
    this->count = newLength;
}

template<class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T> *other) {
    this->items = new DynamicArray<T>(*other);
    this->count = other->GetSize();
}

template<class T>
int ArraySequence<T>::GetLength() const {
    return this->items->GetSize();
}

template<class T>
T ArraySequence<T>::GetFirst() const {
    return (*(this->items))[0];
}

template<class T>
T ArraySequence<T>::GetLast() const {
    return (*(this->items))[this->count - 1];
}

template<class T>
T ArraySequence<T>::Get(const int index) const {
    //return (*(this->items))[index];
    return this->items->Get(index);
}

template<class T>
Sequence<T> *ArraySequence<T>::GetSubsequence(const int start_index, const int end_index) const {
    int new_len = end_index - start_index;
    ArraySequence<T> *newArrSeq = new ArraySequence<T>(new_len);

    for (int i = 0; i < new_len; ++i) {
        newArrSeq->items->Set(i, this->items->Get(start_index + i));
    }

    return newArrSeq;
}

template<class T>
void ArraySequence<T>::Prepend(T value) {
    this->items->Resize(this->count + 1);
    for (int i = this->count; i > 0; --i) {
        (*(this->items))[i] = (*(this->items))[i - 1];
    }
    (*(this->items))[0] = value;

    this->count++;
}

template<class T>
void ArraySequence<T>::Append(T value) {
    this->items->Resize(this->count + 1);
    (*(this->items))[this->count] = value;

    this->count++;
}

template<class T>
void ArraySequence<T>::InsertAt(T value, const int index) {

    if (index < 0 || index > this->count) {
        throw new Exception;
    }

    this->items->Resize(this->count + 1);

    for (int i = this->count; i > index; --i) {
        (*(this->items))[i] = (*(this->items))[i - 1];
    }

    (*(this->items))[index] = value;

    this->count++;

}

template<class T>
void ArraySequence<T>::RemoveAt(const int index) {
    if (this->count <= 1) {
        throw new Exception;
    }

    for (int i = index; i < this->count - 1; ++i) {
        (*(this->items))[i] = (*(this->items))[i + 1];
    }

    this->items->Resize(this->count - 1);
    this->count--;
}

template<class T>
void ArraySequence<T>::Remove(T value) {
    for (int i = 0; i < this->count; ++i) {
        if ((((*(this->items)))[i]).GetValue() == value) {
            this->RemoveAt(i);
            return;
        }
    }
}

template<class T>
void ArraySequence<T>::Remove(bool (*checker)(T item)) {
    for (int i = 0; i < this->count; ++i) {
        if (checker(this->Get(i))) {
            this->RemoveAt(i);
            return;
        }
    }
}

template<class T>
void ArraySequence<T>::RemoveAll(T value) {
    for (int i = 0; i < this->count; ++i) {
        while ((((*(this->items)))[i]).GetValue() == value) {
            this->RemoveAt(i);
        }
    }
}

template<class T>
void ArraySequence<T>::RemoveAll(bool (*checker)(T item)) {
    int i = 0;
    int j = 0;

    int len = this->GetLength();

    for (; i < len; ++i) {
        T toCheck = this->Get(i);
        if (!checker(toCheck) && i == j) {
            j++;
            continue;
        }
        if (!checker(toCheck) && i != j) {
            T temp = this->Get(j);
            Set(toCheck, j);
            Set(temp, i);
            j++;
        }
    }

    this->items->Resize(j);
    this->count = j;
}

template<class T>
Sequence<T> *ArraySequence<T>::Concat(Sequence<T> *other) {
    ArraySequence<T> *newSequence = new ArraySequence<T>(*(Sequence<T>*)this);

    for (int i = 0; i < other->GetLength(); ++i) {
        newSequence->Append((*(this->items))[i]);
    }

    return newSequence;
}

template<class T>
Sequence<T> *ArraySequence<T>::Copy() {
    Sequence<T>* newSequence = new ArraySequence<T>(*(Sequence<T>*)this);
    return newSequence;
}

template<class T>
void ArraySequence<T>::Set(T value, const int index) {

    if (index < 0 || index >= this->count) {
        throw new Exception;
    }

    if (this->count == 1) {
        this->InsertAt(value, 0);
        this->items->Resize(1);
        this->count--;

        return;
    }

    this->RemoveAt(index);

    this->InsertAt(value, index);
}



