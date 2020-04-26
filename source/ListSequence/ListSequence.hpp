#pragma once

#include <iostream>
#include "../Sequence/Sequence.hpp"
#include "../LinkedList/LinkedList.hpp"

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> *items;
    int count{};
public:
    ListSequence(T *items, int count);

    ListSequence(const ListSequence<T> &other);

    ListSequence(Sequence<T> &other);

    ListSequence();

    virtual T GetLength() const override;

    virtual T GetFirst() const override;

    virtual T GetLast() const override;

    virtual T Get(const int index) const override;

    virtual Sequence<T> *GetSubsequence(const int start_index, const int end_index) const override;

    virtual void Prepend(T value) override;

    virtual void Append(T value) override;

    virtual void InsertAt(T value, const int index) override;

    virtual void RemoveAt(const int index) override;

    virtual void Remove(T value) override;

    virtual void RemoveAll(T value) override;

    virtual Sequence<T> *Concat(Sequence<T> *other) override;
};

template<class T>
ListSequence<T>::ListSequence(T *items, int count) {
    this->items = new LinkedList<T>(items, count);
    this->count = count;
}

template<class T>
ListSequence<T>::ListSequence(const ListSequence<T> &other) {
    this->items = new LinkedList<T>(*other.items);
    this->count = other.GetLength();
}

template<class T>
ListSequence<T>::ListSequence(Sequence<T> &other) {
    ListSequence<T> *castedList = static_cast<ListSequence<T> *>(&other);

    if (castedList) {
        this->items = new LinkedList<T>(*castedList->items);
        this->count = castedList->GetLength();

        return;
    }

    int newLength = other.GetLength();
    LinkedList<T> *newList = new LinkedList<T>();
    for (int i = 0; i < newLength; ++i) {
        newList->Append(other.Get(i));
    }
    this->items = newList;
    this->count = newLength;
}

template<class T>
ListSequence<T>::ListSequence() {
    this->items = new LinkedList<T>();
    this->count = 0;
}

template<class T>
T ListSequence<T>::GetLength() const {
    return this->items->GetLength();
}

template<class T>
T ListSequence<T>::GetFirst() const {
    return this->items->GetFirst();
}

template<class T>
T ListSequence<T>::GetLast() const {
    return this->items->GetLast();
}

template<class T>
T ListSequence<T>::Get(const int index) const {
    return this->items->Get(index);
}

template<class T>
Sequence<T> *ListSequence<T>::GetSubsequence(const int start_index, const int end_index) const {
    ListSequence<T> *subsequence = new ListSequence<T>();

    subsequence->items = this->items->GetSubList(start_index, end_index);

    return subsequence;
}

template<class T>
void ListSequence<T>::Prepend(T value) {
    this->items->Prepend(value);
}

template<class T>
void ListSequence<T>::Append(T value) {
    this->items->Append(value);
}

template<class T>
void ListSequence<T>::InsertAt(T value, const int index) {
    this->items->InsertAt(value, index);
}

template<class T>
void ListSequence<T>::RemoveAt(const int index) {
    this->items->RemoveAt(index);
}

template<class T>
void ListSequence<T>::Remove(T value) {
    this->items->Remove(value);
}

template<class T>
void ListSequence<T>::RemoveAll(T value) {
    this->items->RemoveAll(value);
}

template<class T>
Sequence<T> *ListSequence<T>::Concat(Sequence<T> *other) {
    ListSequence<T> *newSequence = new ListSequence<T>(*this);
    ListSequence<T> *castedList = static_cast<ListSequence<T> *>(other);

    if (castedList) {
        newSequence->items = newSequence->items->Concat(castedList->items);
    } else {
        for (int i = 0; i < castedList->GetLength(); i++) {
            newSequence->Append(other->Get(i));
        }
    }

    return newSequence;
}
