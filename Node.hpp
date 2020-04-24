#pragma once

#include <iostream>
#include "Optional.hpp"

using namespace std;

template<class T>
class Node {
public:
    Optional<T>* value;
    Node* next;

    Node(T value) {
        this->value = static_cast<Optional<T>*>(operator new(sizeof(Optional<T>)));
        *(this->value) = value;
        this->next = NULL;
    }
};
