#pragma once

#include "../Dictionary/IDictionary.hpp"
#include "../Dictionary/Pair.hpp"
#include "../BinaryTree/BinaryTree.hpp"

template <class K, class T>
class DictionaryBinaryTree : public IDictionary<K, T> {
private:
    BinaryTree<Pair<K, T>>* items;

    int capacity;
    int count;

public:
    DictionaryBinaryTree(int capacity);

    virtual int Count() const override;

    virtual int Capacity() const override;

    virtual T Get(const K key) const override;

    virtual bool ContainsKey(const K key) const override;

    virtual void Add(const K key, const T element) override;

    virtual void Remove(const K key) override;

    virtual void Change(const K key, T element) override;

    virtual Sequence<K>* GetKeys() override;
};

template<class K, class T>
DictionaryBinaryTree<K, T>::DictionaryBinaryTree(int capacity) {
    this->items = new BinaryTree<Pair<K, T>>();
    this->capacity = capacity;
    this->count = 0;
}

template<class K, class T>
int DictionaryBinaryTree<K, T>::Count() const {
    return this->count;
}

template<class K, class T>
int DictionaryBinaryTree<K, T>::Capacity() const {
    return this->capacity;
}

template<class K, class T>
T DictionaryBinaryTree<K, T>::Get(const K key) const {
    if (this->count <= 0) {
        throw new Exception;
    }

    TreeNode<Pair<K, T>>* resultNode = this->items->Search(Pair<K, T>(key, T()));
    if (resultNode) {
        return resultNode->value->GetSecond();
    }

    throw new Exception;
}

template<class K, class T>
bool DictionaryBinaryTree<K, T>::ContainsKey(const K key) const {
    return (this->items->Search(Pair<K, T>(key, T())) != NULL);
}

template<class K, class T>
void DictionaryBinaryTree<K, T>::Add(const K key, const T element) {
    if (!(this->ContainsKey(key)) && (this->count != this->capacity)) {
        this->items->Insert(Pair<K, T>(key, element));
        this->count++;
    }
}

template<class K, class T>
void DictionaryBinaryTree<K, T>::Remove(const K key) {
    if (this->count <= 0) {
        throw new Exception;
    }

    this->items->DeleteTreeNode(Pair<K, T>(key, T()));
    this->count--;
}

template<class K, class T>
void DictionaryBinaryTree<K, T>::Change(const K key, T element) {
    if (this->count <= 0) {
        throw new Exception;
    }

    TreeNode<Pair<K, T>>* node = this->items->Search(Pair<K, T>(key, T()));
    if (node) {
        node->value = new Pair<K, T>(key, element);
        return;
    }

    throw new Exception;
}

template<class K, class T>
Sequence<K> *DictionaryBinaryTree<K, T>::GetKeys() {
    if (this->count <= 0) {
        throw new Exception;
    }

    Sequence<Pair<K, T>>* tmpSequence = this->items->Get();
    Sequence<K>* resultSequence = new ArraySequence<K>(this->Count());
    for (int i = 0; i < this->count; ++i) {
        resultSequence->Set(tmpSequence->Get(i).GetFirst(), i);
    }

    return resultSequence;
}
