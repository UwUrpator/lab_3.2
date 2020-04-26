#pragma once

#include <iostream>
#include "../source/LinkedList/LinkedList.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class LinkedListTester {
private:
    char *dummyCharArr;
    int dummyCharArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;
public:
    LinkedListTester();

    void TestConstructor1();

    void TestConstructor2();

    void TestConstructor3();
};

LinkedListTester::LinkedListTester() {
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

void LinkedListTester::TestConstructor1() {
    bool isError = false;
    try {
        LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList(T *items, int size); passed: dummyCharArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList(T *items, int size); passed: dummyCharArr, 0" << endl
             << "Not empty list of 0 length was created" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = llistChar->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList(T *items, int size); passed: dummyCharArr, dummyCharArrLen" << endl
                 << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinkedList(T *items, int size); passed: dummyCharArr, dummyCharArrLen" << endl;
    }

    isError = false;

    LinkedList<DummyClass> *llistClass = new LinkedList<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    for (int i = 0; i < this->dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass recievedItem = llistClass->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList(T *items, int size); passed: dummyClassArr, dummyClassArrLen" << endl
                 << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinkedList(T *items, int size); passed: dummyClassArr, dummyClassArrLen" << endl;
    }
}

void LinkedListTester::TestConstructor2() {
    bool isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>();
    try {
        llistChar->GetFirst();
        isError = true;
    } catch (...) {}

    try {
        llistChar->GetLast();
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList(); New list is empty" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList(); New list is not empty" << endl;
    }
}

void LinkedListTester::TestConstructor3() {
    bool isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    LinkedList<char> *llistCharCopied = new LinkedList<char>(*llistChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = llistCharCopied->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList(const LinkedList<T> &list); passed: llistChar (list of chars)" << endl <<
                 "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinkedList(const LinkedList<T> &list); passed: llistChar (list of chars)" << endl;
    }

    isError = false;

    llistChar->InsertAt('z', 0);

    if (llistChar->Get(0) == llistCharCopied->Get(0)) {
        cout << "Error: LinkedList(const LinkedList<T> &list); trying to change source LinkedList (list of chars)"
             << endl << "Copied list changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList(const LinkedList<T> &list); trying to change source LinkedList (list of chars)"
             << endl;
    }

    isError = false;

    LinkedList<DummyClass> *llistClass = new LinkedList<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    LinkedList<DummyClass> *llistClassCopied = new LinkedList<DummyClass>(*llistClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass recievedItem = llistClassCopied->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList(const LinkedList<T> &list); passed: llistClass (list of DummyClass)" << endl
                 << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinkedList(const LinkedList<T> &list); passed: llistClass (list of DummyClass)" << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(456));
    llistClass = new LinkedList<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = llistClass->Get(0);
    DummyClass firstCopied = llistClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout << "Error: LinkedList(const LinkedList<T> &list); trying to change source LinkedList (list of DummyClass)"
             << endl << "Copied list changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList(const LinkedList<T> &list); trying to change source LinkedList (list of chars)"
             << endl;
    }
}

