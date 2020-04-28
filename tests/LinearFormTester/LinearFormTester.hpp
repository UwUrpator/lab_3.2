#pragma once

#include <iostream>
#include "../source/LinearForm/LinearForm.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class LinearFormTester {
private:
    char *dummyCharArr;
    int dummyCharArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;
public:
    LinearFormTester();

    void TestConstructor1();

    void TestSimpleAssign();

    void TestAdditionAssign();
};

LinearFormTester::LinearFormTester() {
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

    TestSimpleAssign();
}

void LinearFormTester::TestConstructor1() {
    bool isError = false;
    try {
        LinearForm<char> *lfChar = new LinearForm<char>(this->dummyCharArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyCharArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: LinearForm(T *items, int size); passed: dummyCharArr, 0" << endl
             << "Not empty array of 0 length was created" << endl;
    }

    isError = false;

    LinearForm<char> *lfChar = new LinearForm<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = lfChar->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm(T *items, int size); passed: dummyCharArr, dummyCharArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyCharArr, dummyCharArrLen" << endl;
    }

    isError = false;

    LinearForm<DummyClass> *lfClass = new LinearForm<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    for (int i = 0; i < this->dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = lfClass->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm(T *items, int size); passed: dummyClassArr, dummyClassArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyClassArr, dummyClassArrLen" << endl;
    }
}

void LinearFormTester::TestSimpleAssign() {
    bool isError = false;

    isError = false;

    LinearForm<char> *lfChar = new LinearForm<char>(this->dummyCharArr, this->dummyCharArrLen);
    LinearForm<char> *lfCharCopied = new LinearForm<char>();

    *lfCharCopied = *lfChar;

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = lfCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator=; passed other LinearForm" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator=; passed other LinearForm" << endl;
    }

    isError = false;

    char* newDummyCharArr = dummyCharArr;
    newDummyCharArr[0] = 'z';

    lfChar = new LinearForm<char>(newDummyCharArr, this->dummyCharArrLen - 1);

    if (lfChar->Get(0) == lfCharCopied->Get(0)) {
        cout << "Error: LinearForm::operator=; trying to change source LinearForm"
             << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: LinearForm::operator=; trying to change source LinearForm"
                << endl;
    }

    isError = false;

    LinearForm<DummyClass> *lfClass = new LinearForm<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    LinearForm<DummyClass> *lfClassCopied = new LinearForm<DummyClass>();

    *lfClassCopied = *lfClass;

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = lfClassCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator=; passed other LinearForm" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator=; passed other LinearForm" << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(456));
    lfClass = new LinearForm<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = lfClass->Get(0);
    DummyClass firstCopied = lfClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout
                << "Error: LinearForm::operator=; trying to change source LinearForm"
                << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: LinearForm::operator=; trying to change source LinearForm"
                << endl;
    }
}

void LinearFormTester::TestAdditionAssign() {
    bool isError = false;
         
}
