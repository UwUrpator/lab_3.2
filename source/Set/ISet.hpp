#pragma once

template <class T>
class ISet {
public:
    virtual void Insert(T value) = 0;

    virtual void Erase(T value) = 0;

    virtual int Count() const = 0;

    virtual T Get(const int index) const = 0;
};
