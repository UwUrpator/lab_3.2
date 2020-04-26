#pragma once

#include <iostream>
#include "../DynamicArray/Optional.hpp"

using namespace std;

template<class T>
class Node {
public:
    T *value;
    Node *next;

    Node(T value);
};

template<class T>
Node<T>::Node(T value) {
    this->value = static_cast<T*>(operator new[](sizeof(T)));
    *this->value = value;
    this->next = NULL;
}
