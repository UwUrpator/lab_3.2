#pragma once

#include <iostream>
#include "../source/LinearForm/LinearForm.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class LinearFormTester {
private:
    int *dummyIntArr;
    int dummyIntArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;
public:
    LinearFormTester();

    void TestConstructor1();

    void TestSimpleAssign();

    void TestAdditionAssign();

    void TestAdd();
};

LinearFormTester::LinearFormTester() {
    this->dummyIntArr = static_cast<int *>(operator new[](3 * sizeof(int)));
    this->dummyIntArr[0] = 1;
    this->dummyIntArr[1] = 2;
    this->dummyIntArr[2] = 3;
    this->dummyIntArrLen = 3;

    this->dummyClassArr = static_cast<DummyClass *>(operator new[](2 * sizeof(DummyClass)));
    DummyClass *dummyClassObj1 = new DummyClass(123);
    DummyClass *dummyClassObj2 = new DummyClass(321);
    this->dummyClassArr[0] = *(dummyClassObj1);
    this->dummyClassArr[1] = *(dummyClassObj2);
    this->dummyClassArrLen = 2;

    TestConstructor1();

    TestSimpleAssign();
    TestAdditionAssign();
    TestAdd();
}

void LinearFormTester::TestConstructor1() {
    bool isError = false;
    try {
        LinearForm<int> *lfChar = new LinearForm<int>(this->dummyIntArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyIntArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: LinearForm(T *items, int size); passed: dummyIntArr, 0" << endl
             << "Not empty array of 0 length was created" << endl;
    }

    isError = false;

    LinearForm<int> *lfChar = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        int expectedItem = this->dummyIntArr[i];
        int receivedItem = lfChar->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm(T *items, int size); passed: dummyIntArr, dummyIntArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyIntArr, dummyIntArrLen" << endl;
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

    LinearForm<int> *lfChar = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    LinearForm<int> *lfCharCopied = new LinearForm<int>();

    *lfCharCopied = *lfChar;

    for (int i = 0; i < dummyIntArrLen; ++i) {
        int expectedItem = this->dummyIntArr[i];
        int receivedItem = lfCharCopied->Get(i);
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

    int* newDummyCharArr = dummyIntArr;
    newDummyCharArr[0] = 4;

    lfChar = new LinearForm<int>(newDummyCharArr, this->dummyIntArrLen - 1);

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
    LinearForm<int> *lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    LinearForm<int> *lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyClassArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i];
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+=; passed other LinearForm (smaller)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyClassArrLen);
    lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i];
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+=; passed other LinearForm (bigger)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        int expectedItem = this->dummyIntArr[i] * 2;
        int receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator+=; passed other LinearForm (equal)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
   }

    if (!isError) {
        cout << "Success: LinearForm::operator+=; passed other LinearForm (equal)" << endl;
    }
}

void LinearFormTester::TestAdd() {
    bool isError = false;
    LinearForm<int> *lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    LinearForm<int> *lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyClassArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i];
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+; passed other LinearForm (smaller)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyClassArrLen);
    lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyClassArrLen) {
            int expectedItem = this->dummyIntArr[i];
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+; passed other LinearForm (bigger)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        int expectedItem = this->dummyIntArr[i] * 2;
        int receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator+; passed other LinearForm (equal)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+; passed other LinearForm (equal)" << endl;
    }
}
