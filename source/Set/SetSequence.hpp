#pragma once

#include "../Set/ISet.hpp"

#include "../Sequence/Sequence.hpp"
#include "../ListSequence/ListSequence.hpp"

template <class T>
class SetSequence : public ISet<T> {
private:
   Sequence<T> *items;
public:
    SetSequence();

    virtual void Insert(T value) override;

    virtual void Erase(T value) override;

    virtual int Count() const override;

    virtual T Get(const int index) const override;
};

template<class T>
SetSequence<T>::SetSequence() {
    this->items = new ListSequence<T>();
}

template<class T>
void SetSequence<T>::Insert(T value) {
    for (int i = 0; i < this->items->GetLength(); ++i) {
        if (this->items->Get(i) == value) {
            this->items->RemoveAt(i);
        }
    }
    this->items->Append(value);
}

template<class T>
void SetSequence<T>::Erase(T value) {
    this->items->Remove(value);
}

template<class T>
int SetSequence<T>::Count() const {
    return this->items->GetLength();
}

template<class T>
T SetSequence<T>::Get(const int index) const {
    return this->items->Get(index);
}
