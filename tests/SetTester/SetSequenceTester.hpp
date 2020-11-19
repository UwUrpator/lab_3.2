#pragma once

#include <iostream>

#include "../source/Set/SetSequence.hpp"
#include "../Informator/Informator.hpp"

class SetSequenceTester {
public:
    SetSequenceTester();

    void TestSetCount();
    void TestSetInsert();
    void TestSetErase();
};

SetSequenceTester::SetSequenceTester() {
    this->TestSetInsert();
    this->TestSetErase();
    this->TestSetCount();
}

void SetSequenceTester::TestSetCount() {
    ISet<int>* set = new SetSequence<int>();

    set->Insert(2);
    set->Insert(2);
    set->Insert(3);
    set->Insert(2);

    Informator(
            (set->Count() == 2),
            "Success: void SetSequence<T>::Count(); Correct count",
            "Error: void SetSequence<T>::Insert(T value); Incorrect count"
    );
}

void SetSequenceTester::TestSetInsert() {
    ISet<int>* set = new SetSequence<int>();

    set->Insert(2);
    set->Insert(2);
    set->Insert(3);
    set->Insert(2);

    Informator(
            (
                set->Get(0) == 3 &&
                set->Get(1) == 2 &&
                set->Count() == 2
            ),
            "Success: void SetSequence<T>::Insert(T value); Inserted correctly",
            "Error: void SetSequence<T>::Insert(T value); Inserted incorrectly"
    );
}

void SetSequenceTester::TestSetErase() {
    ISet<int>* set = new SetSequence<int>();

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
            "Success: void SetSequence<T>::Erase(T value); Erased correctly",
            "Error: void SetSequence<T>::Erase(T value); Erased incorrectly"
    );
}

