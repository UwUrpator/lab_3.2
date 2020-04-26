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

    LinkedList<char>* llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = llistChar->GetIndex(i);
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

    LinkedList<DummyClass>* llistClass = new LinkedList<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    for (int i = 0; i < this->dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass recievedItem = llistClass->GetIndex(i);
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
