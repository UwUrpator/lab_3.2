#pragma once
#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* items;
	int count;
public:
	ArraySequence(const int count) {
		this->items = new DynamicArray<T>(count);
		this->count = count;
	}

	ArraySequence(T* items, int count) {
	    this->items = new DynamicArray<T>(items, count);
        this->count = count;
	}

	ArraySequence(const Sequence<T>& other) {
	    DynamicArray<T>* dynArr = static_cast<DynamicArray<T>*>(*other);
	    if (dynArr) {

	    }
	    this->items = new DynamicArray<T>(*other.items);
        this->count = other.GetLength();
	}

	virtual T GetLength() const override
	{
		return this->items->GetSize();
	}

	virtual T GetFirst() const override
	{
        return (*(this->items))[0];
	}

	virtual T GetLast() const override {
	    return (*(this->items))[this->count - 1];
	}

	virtual T Get(const int index) const override {
	    return (*(this->items))[index];
	}

	virtual Sequence<T>* GetSubsequence(const int start_index, const int end_index) const override {
	    int new_len = end_index - start_index;
	    ArraySequence<T>* newArrSeq = new ArraySequence<T>(new_len);

	    for (int i = 0; i < new_len; ++i) {
	       newArrSeq->items->Set(i, this->items->Get(start_index + i));
	    }

	    return newArrSeq;
	}

	virtual void Prepend(T value) override {
        this->items->Resize(this->count + 1);
        for (int i = this->count; i > 1; --i) {
            (*(this->items))[i] = (*(this->items))[i-1];
        }
        (*(this->items))[0] = value;

        this->count++;
	}

	virtual void Append(T value) override {
        this->items->Resize(this->count + 1);
        (*(this->items))[this->count] = value;

        this->count++;
	}

	virtual void InsertAt(const int index, T value) override {
	    this->items->Resize(this->count + 1);
        for (int i = this->count; i > index + 1; --i) {
            (*(this->items))[i] = (*(this->items))[i-1];
        }
        (*(this->items))[index] = value;

        this->count++;
	}

	virtual void RemoveAt(const int index) override {
	    for (int i = index; i < this->count - 1; ++i) {
            (*(this->items))[i] = (*(this->items))[i + 1];
	    }

	    this->items->Resize(this->count - 1);
	    this->count--;
	}
	virtual void Remove(T value) override {
	    for (int i = 0; i < this->count; ++i) {
	        if (((*(this->items)))[i] == value) {
	            this->RemoveAt(i);
	            return;
	        }
	    }
	}
	virtual void RemoveAll(T value) override {
        for (int i = 0; i < this->count; ++i) {
            if (((*(this->items)))[i] == value) {
                this->RemoveAt(i);
            }
        }
    }

    virtual Sequence<T>* Concat(Sequence<T>* other) override {
	    ArraySequence<T>* newArrSeq = new ArraySequence<T>(*this);

	    for (int i = 0; i < other->GetLength(); ++i) {
	        newArrSeq->Append((*(this->items))[i]);
	    }

	    return newArrSeq;
	}
};
