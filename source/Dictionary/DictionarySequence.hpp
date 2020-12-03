#pragma once

#include "../Dictionary/IDictionary.hpp"
#include "../Dictionary/Pair.hpp"
#include "../ArraySequence/ArraySequence.hpp"

template <class K, class T>
class DictionarySequence : public IDictionary<K, T> {
private:
    Sequence<Pair<K, T>>* items;
    int capacity;
    int count;

public:
    DictionarySequence(int capacity);

    virtual int Count() const override;

    virtual int Capacity() const override;

    virtual T Get(const K key) const override;

    virtual bool ContainsKey(const K key) const override;

    virtual void Add(const K key, const T element) override;

    virtual void Remove(const K key) override;

    virtual void Change(const K key, T element) override;
};

template<class K, class T>
DictionarySequence<K, T>::DictionarySequence(int capacity) {
   this->items = new ArraySequence<Pair<K, T>>(capacity);
   this->capacity = capacity;
   this->count = 0;
}

template<class K, class T>
int DictionarySequence<K, T>::Count() const {
    return this->count;
}

template<class K, class T>
int DictionarySequence<K, T>::Capacity() const {
    return this->capacity;
}

template<class K, class T>
T DictionarySequence<K, T>::Get(const K key) const {
    if (this->count <= 0) {
        throw new Exception;
    }

    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            return this->items->Get(i).GetSecond();
        }
    }

    throw new Exception;
}

template<class K, class T>
bool DictionarySequence<K, T>::ContainsKey(const K key) const {
    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            return true;
        }
    }

    return false;
}

template<class K, class T>
void DictionarySequence<K, T>::Add(const K key, const T element) {
    if (!(this->ContainsKey(key) && (this->count != this->capacity))) {
        this->items->Set(Pair<K, T>(key, element), count);
        this->count++;
    }
    else {
        throw new Exception;
    }
}

template<class K, class T>
void DictionarySequence<K, T>::Remove(const K key) {
    if (this->count <= 0) {
        throw new Exception;
    }

    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            this->items->Remove(this->items->Get(i));
            this->count--;

            return;
        }
    }

    throw new Exception;
}

template<class K, class T>
void DictionarySequence<K, T>::Change(const K key, T element) {
    if (this->count <= 0) {
        throw new Exception;
    }

    for (int i = 0; i < this->count; ++i) {
        if (this->items->Get(i).GetFirst() == key) {
            this->items->Set(Pair<K, T>(key, element), i);
            return;
        }
    }

    throw new Exception;
}
