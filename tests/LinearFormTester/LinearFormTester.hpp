#pragma once

#include <iostream>
#include <complex>
#include "../source/LinearForm/LinearForm.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../DummyClass/DummyClass.hpp"

using namespace std;

class LinearFormTester {
private:
    double *dummyDoubleArr;
    int dummyDoubleArrLen;

    complex<double> *dummyComplexArr;
    int dummyComplexArrLen;
public:
    LinearFormTester();

    void TestConstructor1();

    void TestSimpleAssign();

    void TestAdditionAssign();

    void TestAdd();

    void TestMultiplyAssign();

    void TestMultiply();

    void TestMinusAssign();

    void TestMinus();

    void TestEval();
};

LinearFormTester::LinearFormTester() {
    this->dummyDoubleArr = static_cast<double *>(operator new[](3 * sizeof(double)));
    this->dummyDoubleArr[0] = 1;
    this->dummyDoubleArr[1] = 2;
    this->dummyDoubleArr[2] = 3;
    this->dummyDoubleArrLen = 3;

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
    TestMultiplyAssign();
    TestMultiply();
    TestMinusAssign();
    TestMinus();

    TestEval();
}

void LinearFormTester::TestConstructor1() {
    bool isError = false;
    try {
        LinearForm<double> *lfChar = new LinearForm<double>(this->dummyDoubleArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyDoubleArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: LinearForm(T *items, int size); passed: dummyDoubleArr, 0" << endl
             << "Not empty array of 0 length was created" << endl;
    }

    isError = false;

    LinearForm<double> *lfDouble = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i];
        double receivedItem = lfDouble->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm(T *items, int size); passed: dummyDoubleArr, dummyDoubleArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm(T *items, int size); passed: dummyDoubleArr, dummyDoubleArrLen" << endl;
    }

    isError = false;

    LinearForm<complex<double>> *lfComplex = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                             this->dummyComplexArrLen);
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

    LinearForm<double> *lfDouble = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    LinearForm<double> *lfDoubleCopied = new LinearForm<double>();

    *lfDoubleCopied = *lfDouble;

    for (int i = 0; i < dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i];
        double receivedItem = lfDoubleCopied->Get(i);
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

    double *newDummyDoubleArr = dummyDoubleArr;
    newDummyDoubleArr[0] = 4;

    lfDouble = new LinearForm<double>(newDummyDoubleArr, this->dummyDoubleArrLen - 1);

    if (lfDouble->Get(0) == lfDoubleCopied->Get(0)) {
        cout << "Error: LinearForm::operator=; trying to change source LinearForm"
             << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: LinearForm::operator=; trying to change source LinearForm"
                << endl;
    }

    newDummyDoubleArr[0] = 1;

    isError = false;

    LinearForm<complex<double>> *lfComplex = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                             this->dummyComplexArrLen);
    LinearForm<complex<double>> *lfComplexCopied = new LinearForm<complex<double>>();

    *lfComplexCopied = *lfComplex;

    for (int i = 0; i < dummyComplexArrLen; ++i) {
        complex<double> expectedItem = this->dummyComplexArr[i];
        complex<double> receivedItem = lfComplexCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator=; passed other Complex LinearForm" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator=; passed other Complex LinearForm" << endl;
    }

    isError = false;

    complex<double> *newDummyComplexArr = dummyComplexArr;
    newDummyComplexArr[0] = *(new complex<double>(4.0, 5.0));

    lfComplex = new LinearForm<complex<double>>(newDummyComplexArr, this->dummyComplexArrLen - 1);

    if (lfComplex->Get(0) == lfComplexCopied->Get(0)) {
        cout << "Error: LinearForm::operator=; trying to change source Complex LinearForm"
             << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: LinearForm::operator=; trying to change source Complex LinearForm"
                << endl;
    }

    isError = false;

    newDummyComplexArr[0] = *(new complex<double>(1.0, 2.0));

}

void LinearFormTester::TestAdditionAssign() {

    bool isError = false;
    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    LinearForm<double> *lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {

        if (i < dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i] * 2.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i];
            double receivedItem = lf1->Get(i);
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

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);


    *lf1 += *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i] * 2.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+=; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i];
            double receivedItem = lf1->Get(i);
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

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 += *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i] * 2;
        double receivedItem = lf1->Get(i);
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
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                              this->dummyComplexArrLen);
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
        } else if (i >= 1) {
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
    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    LinearForm<double> *lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i] * 2.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i];
            double receivedItem = lf1->Get(i);
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

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i] * 2.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator+; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i];
            double receivedItem = lf1->Get(i);
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

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 = *lf1 + *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i] * 2.0;
        double receivedItem = lf1->Get(i);
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
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                              this->dummyComplexArrLen);
    LinearForm<complex<double>> *lfComplex2 = new LinearForm<complex<double>>(this->dummyComplexArr, 1);

    LinearForm<complex<double>> lfRes = *lfComplex1 + *lfComplex2;

    //*lfComplex1 = *lfComplex1 + *lfComplex2;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        if (i < 1) {
            complex<double> expectedItem = this->dummyComplexArr[i] * 2.0;
            complex<double> receivedItem = lfRes.Get(i);
            if (!(expectedItem == receivedItem)) {
                cout << "Error: LinearForm::operator+; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= 1) {
            complex<double> expectedItem = this->dummyComplexArr[i];
            complex<double> receivedItem = lfRes.Get(i);
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

void LinearFormTester::TestMultiplyAssign() {
    bool isError = false;
    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 *= 2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i] * 2.0;
        double receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator*=; mult Double items and Double" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }

    }

    if (!isError) {
        cout << "Success: LinearForm::operator*=; mult Double items and Double" << endl;
    }

    isError = false;
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                              this->dummyComplexArrLen);

    *lfComplex1 *= 2.0;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        complex<double> expectedItem = this->dummyDoubleArr[i] * 2.0;
        complex<double> receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator*=; mult Complex items and Double" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator*=; mult Complex items and Double" << endl;
    }
}

void LinearFormTester::TestMultiply() {
    bool isError = false;
    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    LinearForm<double> lfRes = *lf1 * 2;

    //*lf1 = *lf1 * 2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i] * 2.0;
        double receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator*; mult Double items and Double" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }

    }

    if (!isError) {
        cout << "Success: LinearForm::operator*; mult Double items and Double" << endl;
    }

    isError = false;
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                              this->dummyComplexArrLen);
    LinearForm<complex<double>> lfResComplex = *lfComplex1 * 2.0;

    *lfComplex1 = *lfComplex1 * 2.0;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        complex<double> expectedItem = this->dummyDoubleArr[i] * 2;
        complex<double> receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator*; mult Complex items and Double" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator*; mult Complex items and Double" << endl;
    }

}

void LinearFormTester::TestMinusAssign() {
    bool isError = false;
    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    LinearForm<double> *lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);

    *lf1 -= *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = 0.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-=; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i];
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-=; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-=; passed other LinearForm (smaller)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 -= *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = 0.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-=; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = -(this->dummyDoubleArr[i]);
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-=; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-=; passed other LinearForm (bigger)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 -= *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = 0.0;
        double receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator-=; passed other LinearForm (equal)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-=; passed other LinearForm (equal)" << endl;
    }

    isError = false;
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                              this->dummyComplexArrLen);
    LinearForm<complex<double>> *lfComplex2 = new LinearForm<complex<double>>(this->dummyComplexArr, 1);

    *lfComplex1 -= *lfComplex2;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        if (i < 1) {
            complex<double> expectedItem = this->dummyComplexArr[i] * 0.0;
            complex<double> receivedItem = lfComplex1->Get(i);
            if (!(expectedItem == receivedItem)) {
                cout << "Error: LinearForm::operator-=; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= 1) {
            complex<double> expectedItem = this->dummyComplexArr[i];
            complex<double> receivedItem = lfComplex1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-=; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-=; passed other Complex LinearForm (smaller)" << endl;
    }
}

void LinearFormTester::TestMinus() {
    bool isError = false;
    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    LinearForm<double> *lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);

    *lf1 = *lf1 - *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i] * 0.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i];
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-; passed other LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-; passed other LinearForm (smaller)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyComplexArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 = *lf1 - *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        if (i < dummyComplexArrLen) {
            double expectedItem = this->dummyDoubleArr[i] * 0.0;
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= dummyComplexArrLen) {
            double expectedItem = -(this->dummyDoubleArr[i]);
            double receivedItem = lf1->Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-; passed other LinearForm (bigger)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-; passed other LinearForm (bigger)" << endl;
    }

    isError = false;

    lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);
    lf2 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    *lf1 = *lf1 - *lf2;

    for (int i = 0; i < this->dummyDoubleArrLen; ++i) {
        double expectedItem = this->dummyDoubleArr[i] * 0.0;
        double receivedItem = lf1->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: LinearForm::operator-; passed other LinearForm (equal)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-; passed other LinearForm (equal)" << endl;
    }

    isError = false;
    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr,
                                                                              this->dummyComplexArrLen);
    LinearForm<complex<double>> *lfComplex2 = new LinearForm<complex<double>>(this->dummyComplexArr, 1);

    LinearForm<complex<double>> lfRes = *lfComplex1 - *lfComplex2;

    //*lfComplex1 = *lfComplex1 + *lfComplex2;

    for (int i = 0; i < this->dummyComplexArrLen; ++i) {
        if (i < 1) {
            complex<double> expectedItem = this->dummyComplexArr[i] * 0.0;
            complex<double> receivedItem = lfRes.Get(i);
            if (!(expectedItem == receivedItem)) {
                cout << "Error: LinearForm::operator-; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        } else if (i >= 1) {
            complex<double> expectedItem = this->dummyComplexArr[i];
            complex<double> receivedItem = lfRes.Get(i);
            if (expectedItem != receivedItem) {
                cout << "Error: LinearForm::operator-; passed other Complex LinearForm (smaller)" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                break;
            }
        }
    }

    if (!isError) {
        cout << "Success: LinearForm::operator-; passed other Complex LinearForm (smaller)" << endl;
    }
}

void LinearFormTester::TestEval() {
    bool isError = false;

    LinearForm<double> *lf1 = new LinearForm<double>(this->dummyDoubleArr, this->dummyDoubleArrLen);

    double receivedRes = lf1->eval(this->dummyDoubleArr, this->dummyComplexArrLen);
    double expectedRes = 9.0;

    if (receivedRes != expectedRes) {
        cout << "Error: LinearForm<T>::eval(T *values, int size); passed Array of Double" << endl
             << "Expected: " << expectedRes << " Received: " << receivedRes << endl;

        isError = true;
    }
    if (!isError) {
        cout << "Success: LinearForm<T>::eval(T *values, int size); passed Array of Double" << endl;
    }

    isError = false;

    LinearForm<complex<double>> *lfComplex1 = new LinearForm<complex<double>>(this->dummyComplexArr, this->dummyComplexArrLen);

    complex<double> receivedResComplex = lfComplex1->eval(this->dummyComplexArr, this->dummyComplexArrLen - 1);
    complex<double> expectedResComplex = *(new complex<double>(-3.0, 9.0));

    if (receivedResComplex != expectedResComplex) {
        cout << "Error: LinearForm<T>::eval(T *values, int size); passed Array of Complex" << endl
             << "Expected: " << expectedResComplex << " Received: " << receivedResComplex << endl;

        isError = true;
    }
    if (!isError) {
        cout << "Success: LinearForm<T>::eval(T *values, int size); passed Array of Complex" << endl;
    }
}

