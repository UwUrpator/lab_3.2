#pragma once

#include "../Dictionary/IDictionary.hpp"
#include "../Dictionary/Pair.hpp"

using namespace std;

template <class K, class T>
class DictionaryHash : public IDictionary<K, T> {
private:
    struct Node {
        Pair<K, T> value;
        bool state;
        Node(const Pair<K, T> value) : value(value), state(true) {};
    };

    Node** items;

    int capacity;
    int count;
    int countAll;

public:
    DictionaryHash(int const capacity);

    virtual int Count() const override;

    virtual int Capacity() const override;

    virtual T Get(const K key) const override;

    virtual bool ContainsKey(const K key) const override;

    virtual void Add(const K key, const T element) override;

    virtual void Remove(const K key) override;

    virtual void Change(const K key, T element) override;

    virtual Sequence<K>* GetKeys() override;

    int GetHash(K key, int capacity, int seed) const;
    int GetHash1(K key, int capacity) const;
    int GetHash2(K key, int capacity) const;

    void Rehash();
};

template<class K, class T>
DictionaryHash<K, T>::DictionaryHash(int const capacity) {
    this->items = new Node*[capacity];
    this->capacity = capacity;
    this->count = 0;
    this->countAll = 0;

    for (int i = 0; i < capacity; ++i) {
        this->items[i] = nullptr;
    }
}

template<class K, class T>
int DictionaryHash<K, T>::Count() const {
    return this->count;
}

template<class K, class T>
int DictionaryHash<K, T>::Capacity() const {
    return this->capacity;
}

template<class K, class T>
T DictionaryHash<K, T>::Get(const K key) const {
    int hash1 = this->GetHash1(key, this->capacity);
    int hash2 = this->GetHash2(key, this->capacity);
    int i = 0;

    while (this->items[hash1] != nullptr && i < this->capacity) {
        if (this->items[hash1]->value.GetFirst() == key && this->items[hash1]->state)
            return this->items[hash1]->value.GetSecond();
        hash1 = (hash1 + hash2) % this->capacity;
        ++i;
    }

    throw new Exception;
}

template<class K, class T>
bool DictionaryHash<K, T>::ContainsKey(const K key) const {
    int hash1 = this->GetHash1(key, this->capacity);
    int hash2 = this->GetHash2(key, this->capacity);
    int i = 0;

    while (this->items[hash1] != nullptr && i < this->capacity) {
        if (this->items[hash1]->value.GetFirst() == key && this->items[hash1]->state)
            return true;
        hash1 = (hash1 + hash2) % this->capacity;
        ++i;
    }

    return false;
}

template<class K, class T>
void DictionaryHash<K, T>::Add(const K key, const T element) {
    if (this->countAll > 2 * this->count)
        this->Rehash();

     int hash1 = this->GetHash1(key, this->capacity);
     int hash2 = this->GetHash2(key, this->capacity);
    int i = 0;
    int firstDeleted = -1;

    while (this->items[hash1] != nullptr && i < this->capacity) {
        if (this->ContainsKey(key)) {
            return;
        }

        if (!(this->ContainsKey(key)) && !this->items[hash1]->state && firstDeleted == -1) {
            firstDeleted = hash1;
        }

        hash1 = (hash1 + hash2) % this->capacity;
        ++i;
    }

    if (firstDeleted == -1) {
        this->items[hash1] = new Node(Pair<K, T>(key, element));
        this->countAll++;
    }
    else {
        this->items[firstDeleted]->value = Pair<K, T>(key, element);
        this->items[firstDeleted]->state = true;
    }

    this->count++;
}

template<class K, class T>
void DictionaryHash<K, T>::Remove(const K key) {
     int hash1 = this->GetHash1(key, this->capacity);
     int hash2 = this->GetHash2(key, this->capacity);
    int i = 0;

    while (this->items[hash1] != nullptr && i < this->capacity) {
        if (this->items[hash1]->value.GetFirst() == key && this->items[hash1]->state) {
            this->items[hash1]->state = false;
            this->count--;
            return;
        }

        hash1 = (hash1 + hash2) % this->capacity;
        ++i;
    }

    throw new Exception;
}

template<class K, class T>
void DictionaryHash<K, T>::Change(const K key, T element) {
     int hash1 = this->GetHash1(key, this->capacity);
     int hash2 = this->GetHash2(key, this->capacity);
    int i = 0;

    while (this->items[hash1] != nullptr && i < this->capacity) {
        if (this->items[hash1]->value.GetFirst() == key && this->items[hash1]->state) {
            this->items[hash1]->value = Pair<K, T>(key, element);
            return;
        }

        hash1 = (hash1 + hash2) % this->capacity;
        ++i;
    }

    throw new Exception;
}

template<class K, class T>
void DictionaryHash<K, T>::Rehash() {
    this->countAll = 0;
    this->count = 0;
    Node** itemsNew = new Node*[this->capacity];
    for (int i = 0; i < this->capacity; ++i)
        itemsNew[i] = nullptr;
    swap(this->items, itemsNew);
    for (int i = 0; i < this->capacity; ++i) {
        if (itemsNew[i] && itemsNew[i]->state) {
            Pair<K, T> item = itemsNew[i]->value;
            this->Add(item.GetFirst(), item.GetSecond());
        }
    }
}

template<class K, class T>
int DictionaryHash<K, T>::GetHash(K key, int capacity, int seed) const {
    int hash = 0;
    for (int i = 0; i != key.size(); ++i)
        hash = (seed * hash + key[i]) % capacity;
    hash = (hash * 2 + 1) % capacity;
    return hash;
}

template<class K, class T>
int DictionaryHash<K, T>::GetHash1(K key, int capacity) const {
    return this->GetHash(key, capacity, capacity - 1);
}

template<class K, class T>
int DictionaryHash<K, T>::GetHash2(K key, int capacity) const {
    return this->GetHash(key, capacity, capacity + 1);
}

template<class K, class T>
Sequence<K> *DictionaryHash<K, T>::GetKeys() {
    Sequence<K>* resultSequence = new ArraySequence<K>(this->count);
    for (int i = 0; i < this->capacity; ++i) {
        if (this->items[i] && this->items[i]->state) {
            resultSequence->Set(this->items[i]->value.GetFirst(), i);
        }
    }

    return resultSequence;
}
