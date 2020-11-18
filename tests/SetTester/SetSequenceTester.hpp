#pragma once

#include <iostream>

#include "../source/Set/SetSequence.hpp"
#include "../Informator/Informator.hpp"

class SetSequenceTester {
public:
    SetSequenceTester();

    void TestSetInsert();
    void TestSetErase();
    void TestSetCount();
};

SetSequenceTester::SetSequenceTester() {
    this->TestSetInsert();
    //this->TestSetErase();
    //this->TestSetCount();
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
                set->Get(1) == 2
            ),
            "Success: void SetSequence<T>::Insert(T value); Inserted correctly",
            "Error: void SetSequence<T>::Insert(T value); Inserted incorrectly"
    );
}
