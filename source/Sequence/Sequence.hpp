#pragma once

template<class T>
class Sequence {
public:
    virtual int GetLength() const = 0;

    virtual T GetFirst() const = 0;

    virtual T GetLast() const = 0;

    virtual T Get(const int i) const = 0;

    virtual Sequence<T> *GetSubsequence(const int start, const int end) const = 0;

public:
    virtual void Prepend(T value) = 0;

    virtual void Append(T value) = 0;

    virtual void InsertAt(T value, const int index) = 0;

    virtual void RemoveAt(const int index) = 0;

    virtual void Remove(T value) = 0;

    virtual void RemoveAll(T value) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *other) = 0;
};