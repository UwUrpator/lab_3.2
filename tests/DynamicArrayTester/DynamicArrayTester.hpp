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

    void TestGetSize();

    void TestResize();

    void TestGet();
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

    TestGetSize();
    TestResize();
    TestGet();
}

void DynamicArrayTester::TestConstructor1() {
    bool isError = false;

    DynamicArray<char> *darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyCharArrLen);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = darrChar->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: DynamicArray(T* items, int size); passed: dummyIntArr, dummyIntArrLen" << endl <<
                 "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(T* items, int size); passed: dummyIntArr, dummyIntArrLen" << endl;
    }

    isError = false;

    DynamicArray<DummyClass> *darrClass = new DynamicArray<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = darrClass->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: DynamicArray(T* items, int size); passed: dummyComplexArr, dummyComplexArrLen" << endl <<
                 "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(T* items, int size); passed: dummyComplexArr, dummyComplexArrLen" << endl;
    }

    isError = false;

    try {
        DynamicArray<char> *darr_zero = new DynamicArray<char>(this->dummyCharArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray(T* items, int size); passed: dummyIntArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray(T* items, int size); passed: dummyIntArr, 0" << endl <<
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
        cout << "Success: DynamicArray(const int size); passed: dummyIntArrLen" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray(const int size); passed: dummyIntArrLen" << endl <<
             "Item is not Empty";
    }

    isError = false;

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
        char receivedItem = darrCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: DynamicArray(const DynamicArray<T> &array); passed: darrChar (array of chars)" << endl <<
                 "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(const DynamicArray<T> &array); passed: darrChar (array of chars)" << endl;
    }

    isError = false;

    (*darrChar)[0] = 'z';

    if (darrChar->Get(0) == darrCharCopied->Get(0)) {
        cout << "Error: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
             << endl << "Copied array changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout << "Success: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
             << endl;
    }

    isError = false;

    DynamicArray<DummyClass> *darrClass = new DynamicArray<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    DynamicArray<DummyClass> *darrClassCopied = new DynamicArray<DummyClass>(*darrClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = darrClassCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: DynamicArray(const DynamicArray<T> &array); passed: darrClass (array of DummyClass)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: DynamicArray(const DynamicArray<T> &array); passed: darrClass (array of DummyClass)" << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(456));
    darrClass = new DynamicArray<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = darrClass->Get(0);
    DummyClass firstCopied = darrClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout << "Error: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray" << endl
             << "Copied array changes after changing of source (array of DummyClass)";
        isError = true;
    }

    if (!isError) {
        cout << "Success: DynamicArray(const DynamicArray<T> &array); trying to change source DynamicArray (array of DummyClass)"
             << endl;
    }
}

void DynamicArrayTester::TestGetSize() {
    bool isError = false;

    DynamicArray<char> *darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyCharArrLen);

    int darrCharSize = darrChar->GetSize();
    if (this->dummyCharArrLen == darrCharSize) {
        cout << "Success: DynamicArray::GetSize(); returns correct size" << endl;
    } else {
        isError = true;

        cout << "Error: DynamicArray::GetSize(); returns incorrectsize" << endl << "Expected: "
             << this->dummyCharArrLen << " Received: " << darrCharSize << endl;
    }

    isError = false;

    DynamicArray<char> *darrCharEmpty = new DynamicArray<char>(this->dummyCharArrLen);

    int darrCharEmptySize = darrCharEmpty->GetSize();
    if (this->dummyCharArrLen == darrCharEmptySize) {
        cout << "Success: DynamicArray::GetSize(); returns correct size of empty array" << endl;
    } else {
        isError = true;

        cout << "Error: DynamicArray::GetSize(); returns incorrectsize of empty array" << endl << "Expected: "
             << this->dummyCharArrLen << " Received: " << darrCharSize << endl;
    }
}

void DynamicArrayTester::TestResize() {
    bool isError = false;

    DynamicArray<char>* darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyClassArrLen);

    try {
        darrChar->Resize(0);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray::Resize(int newSize); array of 0 length was not created" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray::Resize(int newSize); array of 0 length was created" << endl;
    }

    isError = false;

    darrChar->Resize(1);
    if (darrChar->GetSize() == 1 && darrChar->Get(0) == this->dummyCharArr[0]) {
        cout << "Success: DynamicArray::Resize(int newSize); new size 1" << endl;
    } else {
        cout << "Error: DynamicArray::Resize(int newSize); new size was not set correctly" << endl;
    }

    isError = false;

    darrChar->Resize(2);
    if (darrChar->GetSize() == 2 && darrChar->Get(0) == this->dummyCharArr[0]) {
        try {
            darrChar->Get(1);
            isError = true;
        } catch (...) {
            cout << "Success: DynamicArray::Resize(int newSize); new size 2" << endl;
        }

        if (isError) {
            cout << "Error: DynamicArray::Resize(int newSize); new size 2 was not set correctly" << endl;
        }
    } else {
        cout << "Error: DynamicArray::Resize(int newSize); new size 2 was not set correctly" << endl;
    }
}

void DynamicArrayTester::TestGet() {
    bool isError = false;

    DynamicArray<char> *darrCharEmpty = new DynamicArray<char>(this->dummyCharArrLen);
    try {
        darrCharEmpty->Get(0);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray::Get(int index); Item of empty array was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray::Get(int index); Item of empty array was gotten" << endl;
    }

    isError = false;

    DynamicArray<char> *darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyCharArrLen);

    try {
        darrCharEmpty->Get(-1);
        isError = true;
    } catch (...) {
        cout << "Success: DynamicArray::Get(int index); Item with incorrect index was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: DynamicArray::Get(int index); Item with incorrect index was gotten" << endl;
    }

    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = darrChar->Get(i);

        if (expectedItem != receivedItem) {
            cout << "Error: DynamicArray::Get(int index); Wrong index item" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
            isError = true;
            break;
        }
    }
    if (!isError) {
        cout << "Success: DynamicArray::Get(int index); Correct index item" << endl;
    }
}
