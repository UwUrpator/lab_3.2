#pragma once

#include <string>
#include <iostream>

using namespace std;

template<typename T>
class TreeNode {
public:
    T* value;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode<T>(T value);
};

template<class T>
TreeNode<T>::TreeNode(T value) {
    //this->value = static_cast<T*>(operator new[](sizeof(T) + 1));
    this->value = new T();

    *this->value = value;

    this->left = NULL;
    this->right = NULL;
}