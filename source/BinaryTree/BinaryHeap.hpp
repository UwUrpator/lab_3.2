#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "../../Exception.hpp"

using namespace std;

template<typename T>
class BinaryHeap {
public:
    BinaryHeap();
    ~BinaryHeap();

    void insert(T value);

    T remove(int index);

    T search(int index);

    string toString(string bypass = "KLR");

private:
    vector<T> heap;

    int _getLeftChild(int parent);

    int _getRightChild(int parent);

    int _getParent(int child);

    void _bubbleUp(int index);

    void _bubbleDown(int index);

    bool _isLeaf(int index);

    string _toString(string bypass, int parent);
};

template<typename T>
BinaryHeap<T>::BinaryHeap() {
    this->heap = vector<T>();
}

template<typename T>
BinaryHeap<T>::~BinaryHeap() {
    heap.clear();
}

template<typename T>
int BinaryHeap<T>::_getParent(int child) {
    if (child % 2 == 0)
        return (child / 2) - 1;
    else
        return child / 2;
}

template<typename T>
void BinaryHeap<T>::_bubbleUp(int index) {
    if (index == 0) {
        return;
    }

    int parent = this->_getParent(index);

    if (heap[parent] < heap[index]) {
        T tmp = heap[parent];
        heap[index] = tmp;
        this->_bubbleUp(parent);
    }
}

template<typename T>
void BinaryHeap<T>::_bubbleDown(int index) {
    int left = this->_getLeftChild(index);
    int right = this->_getRightChild(index);

    if (this->_isLeaf(left)) {
        return;
    }

    int maxIndex = index;

    if(heap[left] > heap[index])
    {
        maxIndex = left;
    }

    if(!this->_isLeaf(right) && (heap[right] > heap[maxIndex]))
    {
        maxIndex = right;
    }

    if(maxIndex != index)
    {
        T temp = heap[index];
        heap[index] = heap[maxIndex];
        heap[maxIndex] = temp;
        this->_bubbleDown(maxIndex);
    }
}

template<typename T>
bool BinaryHeap<T>::_isLeaf(int index) {
    if (index >= heap.size()) {
        return true;
    }
    return false;
}

template<typename T>
void BinaryHeap<T>::insert(T value) {
    heap.push_back(value);
    this->_bubbleUp(heap.size()-1);
}

template<typename T>
int BinaryHeap<T>::_getLeftChild(int parent) {
    return 2 * parent + 1;
}

template<typename T>
int BinaryHeap<T>::_getRightChild(int parent) {
    return 2 * parent + 2;
}

template<typename T>
string BinaryHeap<T>::toString(string bypass) {
    return this->_toString(bypass, 0);
}

template<typename T>
string BinaryHeap<T>::_toString(string bypass, int parent) {
    if (heap.size() == 0) {
        throw new Exception;
    }

    stringstream strs;

    if (parent >= 0) {
        for (int i = 0; i < bypass.length(); i++) {
            switch (bypass[i]) {
                case 'K':
                    strs << "{" << heap[parent] << "}";
                    break;
                case 'L':
                    if (this->_getLeftChild(parent) < heap.size()) {
                        strs << "(" << this->_toString(bypass, this->_getLeftChild(parent)) << ")";
                    }
                    break;
                case 'R':
                    if (this->_getRightChild(parent) < heap.size()) {
                        strs << "[" << this->_toString(bypass, this->_getRightChild(parent)) << "]";
                    }
                    break;
            }
        }
    }

    return strs.str();
}

template<typename T>
T BinaryHeap<T>::remove(int index) {

    T r = heap[index];

    heap[index] = heap[heap.size()-1];
    heap.pop_back();
    int p = this->_getParent(index);
    if(index == 0 || heap[index] < heap[p])
        this->_bubbleDown(index);
    else
        this->_bubbleUp(index);
    return r;
}

template<typename T>
T BinaryHeap<T>::search(int index) {
    return heap[index];
}








