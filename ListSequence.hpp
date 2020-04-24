#pragma once

#include <iostream>
#include "Sequence.hpp"
#include "LinkedList.hpp"

template <class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;
    int count;
public:
    ListSequence(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
        this->count = count;
    }

    ListSequence(const ListSequence<T>& other) {
        this->items = new LinkedList<T>(*other.items);
        this->count = other.GetLength();
    }
    ListSequence(const Sequence<T>& other) {
        ListSequence<T>* castedList = static_cast<ListSequence<T>*>(*other);

        if (castedList) {
            this->items = castedList;
        }
        else {
            this->items = new ListSequence<T>(*other.items);
            this->count = other.GetLength();
        }
    }

    ListSequence() {
        this->items = new LinkedList<T>();
        this->count = 0;
    }

    virtual T GetLength() const override
    {
        return this->items->GetLength();
    }

    virtual T GetFirst() const override
    {
        return this->items->GetFirst();
    }

    virtual T GetLast() const override {
        return this->items->GetLast();
    }

    virtual T Get(const int index) const override {
        return this->items->GetIndex(index);
    }

    virtual Sequence<T>* GetSubsequence(const int start_index, const int end_index) const override {
        ListSequence<T>* subsequence = new ListSequence<T>();

        subsequence->items = this->items->GetSubList(start_index, end_index);

        return subsequence;
    }

    virtual void Prepend(T value) override {
        this->items->Prepend(value);
    }

    virtual void Append(T value) override {
        this->items->Append(value);
    }

    virtual void InsertAt(T value, const int index) override {
        this->items->InsertAt(value, index);
    }

    virtual void RemoveAt(const int index) override {
        this->items->RemoveAt(index);
    }

    virtual void Remove(T value) override {
        this->items->Remove(value);
    }

    virtual void RemoveAll(T value) override {
        this->items->RemoveAll(value);
    }

    virtual Sequence<T>* Concat(Sequence<T>* other) override {
        ListSequence<T>* newSequence = new ListSequence<T>(*this);
        ListSequence<T>* castedList = static_cast<ListSequence<T>*>(other);

        if (castedList) {
            newSequence->items = newSequence->items->Concat(castedList->items);
        }
        else {
            for (int i = 0; i < castedList->GetLength(); i++) {
                newSequence->Append(other->Get(i));
            }
        }

        return newSequence;
    }
};
