#pragma once

#include <iostream>
#include "../source/DynamicArray/DynamicArray.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class ArraySequenceTester {
private:
    char *dummyCharArr;
    int dummyCharArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;

    DynamicArray<char> *dummyCharDArr;
    DynamicArray<DummyClass> *dummyClassDArr;

public:
    ArraySequenceTester();


};
