#pragma once

#include "../Set/ISet.hpp"

#include "../BinaryTree/BinaryTree.hpp"

template <class T>
class SetBinaryTree : public ISet<T> {
private:
    BinaryTree<T> *items;
public:
    SetBinaryTree();

    virtual void Insert(T value) override;

    virtual void Erase(T value) override;

    virtual int Count() const override;

    virtual T Get(const int index) const override;
};

template<class T>
SetBinaryTree<T>::SetBinaryTree() {
    this->items = new BinaryTree<T>();
}

template<class T>
void SetBinaryTree<T>::Insert(T value) {
    this->items->Insert(value);
}
