#pragma once

#include <iostream>
#include "../source/DynamicArray/DynamicArray.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class DynamicArrayTester {
private:
    char *dummyCharArr;
    int dummyCharArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;

public:
    DynamicArrayTester();

    void TestConstructor1();

    void TestConstructor2();

    void TestConstructor3();
};

DynamicArrayTester::DynamicArrayTester() {
    this->dummyCharArr = static_cast<char *>(operator new[](3 * sizeof(char)));
    this->dummyCharArr[0] = 'a';
    this->dummyCharArr[1] = 'b';
    this->dummyCharArr[2] = 'c';
    this->dummyCharArrLen = 3;

    this->dummyClassArr = static_cast<DummyClass *>(operator new[](2 * sizeof(DummyClass)));
    DummyClass *dummyClassObj1 = new DummyClass(123);
    DummyClass *dummyClassObj2 = new DummyClass(321);
    this->dummyClassArr[0] = *(dummyClassObj1);
    this->dummyClassArr[1] = *(dummyClassObj2);
    this->dummyClassArrLen = 2;

    TestConstructor1();
    TestConstructor2();
    TestConstructor3();
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
}

void DynamicArrayTester::TestConstructor2() {
    bool isError = false;

    DynamicArray<char> *darr = new DynamicArray<char>(this->dummyCharArrLen);

    try {
        darr->Get(0);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray(const int size); passed: dummyCharArrLen" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray(const int size); passed: dummyCharArrLen" << endl <<
             "Item is not Empty";
    }

    try {
        DynamicArray<char> *darr_zero = new DynamicArray<char>(0);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray(const int size); passed: 0" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray(const int size); passed: 0" << endl <<
             "DynamicArray with 0 length was created";
    }
}

void DynamicArrayTester::TestConstructor3() {
    bool isError = false;

    DynamicArray<char> *darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyCharArrLen);
    DynamicArray<char> *darrCharCopied = new DynamicArray<char>(*darrChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = darrCharCopied->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: DynamicArray(const DynamicArray<T> &array); passed: darrChar (array of chars)" << endl <<
                 "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(const DynamicArray<T> &array); passed: darrChar (array of chars)" << endl;
    }

    (*darrChar)[0] = 'z';

    if (darrChar->Get(0) == darrCharCopied->Get(0)) {
        cout
                << "Error: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
                << endl <<
                "Copied array changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
                << endl;
    }


    DynamicArray<DummyClass> *darrClass = new DynamicArray<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    DynamicArray<DummyClass> *darrClassCopied = new DynamicArray<DummyClass>(*darrClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass recievedItem = darrClassCopied->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: DynamicArray(const DynamicArray<T> &array); passed: darrClass (array of DummyClass)" << endl
                 <<
                 "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(const DynamicArray<T> &array); passed: darrClass (array of DummyClass)" << endl;
    }

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(456));
    darrClass = new DynamicArray<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = darrClass->Get(0);
    DummyClass firstCopied = darrClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout << "Error: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray" << endl <<
             "Copied array changes after changing of source (array of DummyClass)";
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray (array of DummyClass)"
                << endl;
    }
}

