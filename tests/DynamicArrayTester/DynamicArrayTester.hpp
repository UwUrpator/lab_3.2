#pragma once

#include <iostream>
#include "../source/DynamicArray/DynamicArray.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class DynamicArrayTester {
private:
    char* dummyCharArr;
    int dummyCharArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;

public:
    DynamicArrayTester();

    void TestConstructor1();
};

DynamicArrayTester::DynamicArrayTester() {
    this->dummyCharArr = static_cast<char *>(operator new[](3 * sizeof(char)));
    this->dummyCharArr[0] = 'a';
    this->dummyCharArr[1] = 'b';
    this->dummyCharArr[2] = 'c';
    this->dummyCharArrLen = 3;

    this->dummyClassArr = static_cast<DummyClass *>(operator new[](2 * sizeof(DummyClass)));
    DummyClass* dummyClassObj1 = new DummyClass(123);
    DummyClass* dummyClassObj2 = new DummyClass(321);
    this->dummyClassArr[0] = *(dummyClassObj1);
    this->dummyClassArr[1] = *(dummyClassObj2);
    this->dummyClassArrLen = 2;

    TestConstructor1();
}

void DynamicArrayTester::TestConstructor1() {
    bool isError = false;

    DynamicArray<char> *darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyCharArrLen);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = darrChar->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: DynamicArray(T* items, int size); passed: dummyCharArr, dummyCharArrLen" << endl <<
                 "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(T* items, int size); passed: dummyCharArr, dummyCharArrLen" << endl;
    }

    try {
        DynamicArray<char> *darr_zero = new DynamicArray<char>(this->dummyCharArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray(T* items, int size); passed: dummyCharArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray(T* items, int size); passed: dummyCharArr, 0" << endl <<
             "DynamicArray with 0 length was created";
    }

    DynamicArray<DummyClass> *darrClass = new DynamicArray<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass recievedItem = darrClass->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: DynamicArray(T* items, int size); passed: dummyClassArr, dummyClassArrLen" << endl <<
                 "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(T* items, int size); passed: dummyClassArr, dummyClassArrLen" << endl;
    }
}

