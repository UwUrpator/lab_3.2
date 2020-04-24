#pragma once
#include "Exception.hpp"
#include <iostream>

using namespace std;
//#include "DynamicArray2.hpp"

template <class T>
class Optional {
private:
	static Optional<T>* empty; // define what is empty value
	static bool emptyIsSet; // is empty value set
    T value; // value of Optional
    bool hasValue; // is value of Optional set
    
public:
    // return empty value
	static Optional<T>* Empty()
	{
		if (!emptyIsSet) {
            empty = new Optional<T>();
            emptyIsSet = true;
        }
		return empty;
	}

	// constuctor
	Optional(T value) 
	{
		this->value = value;
		this->hasValue = true;
	}

    // get value of Optional
    T GetValue() const
    {
        if (this->hasValue)
            return this->value;
        else
            throw new Exception; // Invalid Operation Exception
    }
    
    // check if Optional has value
    bool HasValue() const { 
	    return this->hasValue;
	}
    
	// check if Optional`s value is equal to parameter
    bool TryGetValue(T& value) const {
        if (!this->hasValue)
            return false;
        value = this->value;
        return true;
    }
    
    // equal operator
    bool operator==(Optional<T>& other) {
        return this->hasValue == other->hasValue && (!this->hasValue || this->value == other->value);
    }
    
    operator T() const {
        if (!this->hasValue)
            return false;
        return this->value;
    }

private:
    // create empty Optional
	Optional()
	{
		this->hasValue = false;
	}
};

template<class T>
bool Optional<T>::emptyIsSet;

template<class T>
Optional<T>* Optional<T>::empty;
