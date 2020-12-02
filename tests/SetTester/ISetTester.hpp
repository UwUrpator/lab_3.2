#pragma once

#include <iostream>
#include "string"

#include "../source/Set/ISet.hpp"
#include "../Informator/Informator.hpp"

template<class T>
class ISetTester {
public:
    ISetTester<T>(string name);

private:
    string name;

    void TestSetCount();

    void TestSetInsert();

    void TestSetErase();
};

template<class T>
ISetTester<T>::ISetTester(string name) {
    this->name = name;

    this->TestSetInsert();
    this->TestSetErase();
    this->TestSetCount();
}

template<class T>
void ISetTester<T>::TestSetCount() {
    ISet<int>* set = new T();

    set->Insert(2);
    set->Insert(2);
    set->Insert(3);
    set->Insert(2);

    Informator(
            (set->Count() == 2),
            "Success: void " + this->name + "::Count(); Correct count",
            "Error: void " + this->name + "::Count(); Incorrect count"
    );
}

template<class T>
void ISetTester<T>::TestSetInsert() {
    ISet<int>* set = new T();

    set->Insert(2);
    set->Insert(2);
    set->Insert(3);
    set->Insert(2);

    Informator(
            (
                    set->Get(0) == 3 &&
                    set->Get(1) == 2 &&
                    set->Count() == 2
            ) ||
            (
                    set->Get(0) == 2 &&
                    set->Get(1) == 3 &&
                    set->Count() == 2
            ),
            "Success: void " + this->name + "::Insert(T value); Inserted correctly",
            "Error: void " + this->name + "::Insert(T value); Inserted incorrectly"
    );
}

template<class T>
void ISetTester<T>::TestSetErase() {
    ISet<int>* set = new T();

    set->Insert(2);
    set->Insert(2);
    set->Insert(3);
    set->Insert(2);

    set->Erase(3);

    Informator(
            (
                    set->Get(0) == 2 &&
                    set->Count() == 1
            ),
            "Success: void " + this->name + "::Erase(T value); Erased correctly",
            "Error: void " + this->name + "::Erase(T value); Erased incorrectly"
    );
}
