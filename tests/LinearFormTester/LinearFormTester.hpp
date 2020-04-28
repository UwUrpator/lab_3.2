#pragma once

#include <iostream>
#include <complex>
#include "../source/LinearForm/LinearForm.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class LinearFormTester {
private:
    int *dummyIntArr;
    int dummyIntArrLen;

    complex<double> *dummyComplexArr;
    int dummyComplexArrLen;
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

    this->dummyComplexArr = static_cast<complex<double> *>(operator new[](2 * sizeof(complex<double>)));
    complex<double> *dummyComplex1 = new complex<double>(1.0, 2.0);
    complex<double> *dummyComplex2 = new complex<double>(2.0, 3.0);
    this->dummyComplexArr[0] = *(dummyComplex1);
    this->dummyComplexArr[1] = *(dummyComplex2);
    this->dummyComplexArrLen = 2;

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

    LinearForm<int> *lfInt = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        int expectedItem = this->dummyIntArr[i];
        int receivedItem = lfInt->Get(i);
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

    LinearForm<complex<double>> *lfComplex = new LinearForm<complex<double>>(this->dummyComplexArr, this->dummyComplexArrLen);
    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        complex<double> expectedItem = this->dummyComplexArr[i];
        complex<double> receivedItem = lfComplex->Get(i);
        if (!(expectedItem == receivedItem)) {
            cout << "Error: LinearForm(T *items, int size); passed: dummyComplexArr, dummyComplexArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyComplexArr, dummyComplexArrLen" << endl;
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

    int* newDummyIntArr = dummyIntArr;
    newDummyIntArr[0] = 4;

    lfChar = new LinearForm<int>(newDummyIntArr, this->dummyIntArrLen - 1);

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

}

void LinearFormTester::TestAdditionAssign() {
    bool isError = false;
    LinearForm<int> *lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    LinearForm<int> *lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyComplexArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyComplexArrLen) {
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

    lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyComplexArrLen);
    lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyComplexArrLen) {
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

    isError = false;
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr, this->dummyComplexArrLen);
    LinearForm<complex<double>> *lfComplex2 = new LinearForm<complex<double>>(this->dummyComplexArr, 1);

    *lfComplex1 += *lfComplex2;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        if (i < 1) {
            complex<double> expectedItem = this->dummyComplexArr[i] * 2.0;
            complex<double> receivedItem = lfComplex1->Get(i);
            if (!(expectedItem == receivedItem)) {
                cout << "Error: LinearForm::operator+=; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= 1) {
            complex<double> expectedItem = this->dummyComplexArr[i];
            complex<double> receivedItem = lfComplex1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+=; passed other Complex LinearForm (smaller)" << endl;
    }
}

void LinearFormTester::TestAdd() {
    bool isError = false;
    LinearForm<int> *lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);
    LinearForm<int> *lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyComplexArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyComplexArrLen) {
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

    lf1 = new LinearForm<int>(this->dummyIntArr, this->dummyComplexArrLen);
    lf2 = new LinearForm<int>(this->dummyIntArr, this->dummyIntArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyIntArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            int expectedItem = this->dummyIntArr[i] * 2;
            int receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= dummyComplexArrLen) {
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

    isError = false;
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr, this->dummyComplexArrLen);
    LinearForm<complex<double>> *lfComplex2 = new LinearForm<complex<double>>(this->dummyComplexArr, 1);

    *lfComplex1 = *lfComplex1 + *lfComplex2;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        if (i < 1) {
            complex<double> expectedItem = this->dummyComplexArr[i] * 2.0;
            complex<double> receivedItem = lfComplex1->Get(i);
            if (!(expectedItem == receivedItem)) {
                cout << "Error: LinearForm::operator+; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
        else if (i >= 1) {
            complex<double> expectedItem = this->dummyComplexArr[i];
            complex<double> receivedItem = lfComplex1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator+; passed other Complex LinearForm (smaller)" << endl;
    }
}
