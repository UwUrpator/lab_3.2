#pragma once

#include "../Sequence/Sequence.hpp"
#include "../ListSequence/ListSequence.hpp"

template <class K, class T>
class IDictionary {
public:
    virtual int Count() const = 0;

    virtual int Capacity() const = 0;

    virtual T Get(const K key) const = 0;

    virtual bool ContainsKey(const K key) const = 0;

    virtual void Add(const K key, const T element) = 0;

    virtual void Remove(const K key) = 0;

    virtual void Change(const K key, T element) = 0;
};
