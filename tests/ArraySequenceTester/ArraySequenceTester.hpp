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
public:
    ArraySequenceTester();

    void TestConstructor1();

    void TestConstructor2();

    void TestConstructor3();

    void TestConstructor4();

    void TestGetLength();

    void TestGetFirst();

    void TestGetLast();

    void TestGet();

    void TestGetSubsequence();

    void TestPrepend();

    void TestAppend();

    void TestInsertAt();

    void TestRemoveAt();

    void TestRemove();

    void TestRemoveAll();

    void TestConcat();

    void TestCopy();

    void TestSet();
};

ArraySequenceTester::ArraySequenceTester() {
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
    TestConstructor4();

    TestGetLength();
    TestGetFirst();
    TestGetLast();
    TestGet();
    TestGetSubsequence();

    TestPrepend();
    TestAppend();
    TestInsertAt();

    TestRemoveAt();
    TestRemove();
    TestRemoveAll();
    TestConcat();

    TestCopy();
    TestSet();
}

void ArraySequenceTester::TestConstructor1() {
    bool isError = false;
    try {
        ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: ArraySequence(T *items, int size); passed: dummyIntArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: ArraySequence(T *items, int size); passed: dummyIntArr, 0" << endl
             << "Not empty array of 0 length was created" << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = asChar->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence(T *items, int size); passed: dummyIntArr, dummyIntArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence(T *items, int size); passed: dummyIntArr, dummyIntArrLen" << endl;
    }

    isError = false;

    ArraySequence<DummyClass> *asClass = new ArraySequence<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    for (int i = 0; i < this->dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = asClass->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence(T *items, int size); passed: dummyComplexArr, dummyComplexArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence(T *items, int size); passed: dummyComplexArr, dummyComplexArrLen" << endl;
    }
}

void ArraySequenceTester::TestConstructor2() {
    bool isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArrLen);
    try {
        asChar->GetFirst();
        isError = true;
    } catch (...) {}

    try {
        asChar->GetLast();
        isError = true;
    } catch (...) {
        cout << "Success: ArraySequence(); New array is empty" << endl;
    }

    if (isError) {
        cout << "Error: ArraySequence(); New array is not empty" << endl;
    }
}

void ArraySequenceTester::TestConstructor3() {
    bool isError = false;

    isError = false;

    DynamicArray<char> *darrChar = new DynamicArray<char>(this->dummyCharArr, this->dummyCharArrLen);
    ArraySequence<char> *asCharCopied = new ArraySequence<char>(darrChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = asCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence(const DynamicArray<T> &array); passed: arrayChar (array of chars)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence(const DynamicArray<T> &array); passed: arrayChar (array of chars)" << endl;
    }

    isError = false;

    (*darrChar)[0] = 'z';

    if (darrChar->Get(0) == asCharCopied->Get(0)) {
        cout
                << "Error: ArraySequence(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
                << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: ArraySequence(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
                << endl;
    }

    isError = false;

    DynamicArray<DummyClass> *darrClass = new DynamicArray<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    ArraySequence<DummyClass> *asClassCopied = new ArraySequence<DummyClass>(darrClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = asClassCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence(const DynamicArray<T> &array); passed: arrayClass (array of DummyClass)"
                 << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence(const DynamicArray<T> &array); passed: arrayClass (array of DummyClass)"
             << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(456));
    darrClass = new DynamicArray<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = darrClass->Get(0);
    DummyClass firstCopied = asClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout
                << "Error: ArraySequence(const DynamicArray<T> &array); trying to change source DynamicArray (array of DummyClass)"
                << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: ArraySequence(const DynamicArray<T> &array); trying to change source DynamicArray (array of chars)"
                << endl;
    }
}

void ArraySequenceTester::TestConstructor4() {
    bool isError = false;

    isError = false;

    Sequence<char> *sChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    ArraySequence<char> *asCharCopied = new ArraySequence<char>(*sChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = asCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence(const Sequence<T> &array); passed: sChar (seq of chars)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence(const Sequence<T> &array); passed: sChar (seq of chars)" << endl;
    }

    isError = false;

    sChar->InsertAt('z', 0);

    if (sChar->Get(0) == asCharCopied->Get(0)) {
        cout << "Error: ArraySequence(const Sequence<T> &array); trying to change source Sequence (seq of chars)"
             << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence(const Sequence<T> &array); trying to change source Sequence (seq of chars)"
             << endl;
    }

    isError = false;

    Sequence<DummyClass> *sClass = new ArraySequence<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    ArraySequence<DummyClass> *asClassCopied = new ArraySequence<DummyClass>(*sClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = asClassCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence(const Sequence<T> &array); passed: sClass (seq of DummyClass)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence(const Sequence<T> &array); passed: sClass (seq of DummyClass)" << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(789));
    sClass = new ArraySequence<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = sClass->Get(0);
    DummyClass firstCopied = asClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout << "Error: ArraySequence(const Sequence<T> &array); trying to change source Sequence (seq of DummyClass)"
             << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence(const Sequence<T> &array); trying to change source Sequence (seq of chars)"
             << endl;
    }
}

void ArraySequenceTester::TestGetLength() {
    bool isError = false;

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);

    int expectedLen = this->dummyCharArrLen;
    int receivedLen = asChar->GetLength();

    if (expectedLen != receivedLen) {
        cout << "Error: ArraySequence::TestGetLength(); Length of arrayseq is incorrect" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::TestGetLength(); Length of arrayseq is correct" << endl;
    }

}

void ArraySequenceTester::TestGetFirst() {
    bool isError = false;

    ArraySequence<char> *asCharEmpty = new ArraySequence<char>(this->dummyCharArrLen);
    try {
        asCharEmpty->GetFirst();
        isError = true;
    } catch (...) {
        cout << "Success: ArraySequence::GetFirst(); First item of empty arrayseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ArraySequence::GetFirst(); First item of empty arrayseq was gotten" << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyClassArrLen);
    char expectedItem = this->dummyCharArr[0];
    char receivedItem = asChar->GetFirst();

    if (expectedItem != receivedItem) {
        cout << "Error: ArraySequence::GetFirst(); Wrong first item" << endl
             << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
        isError = true;
    } else {
        cout << "Success: ArraySequence::GetFirst(); Correct first item" << endl;
    }

}

void ArraySequenceTester::TestGetLast() {
    bool isError = false;

    ArraySequence<char> *asCharEmpty = new ArraySequence<char>(this->dummyCharArrLen);
    try {
        asCharEmpty->GetLast();
        isError = true;
    } catch (...) {
        cout << "Success: ArraySequence::GetLast(); Last item of empty arrayseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ArraySequence::GetLast(); Last item of empty arrayseq was gotten" << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    char expectedItem = this->dummyCharArr[this->dummyCharArrLen - 1];
    char receivedItem = asChar->GetLast();

    if (expectedItem != receivedItem) {
        cout << "Error: ArraySequence::GetLast(); Wrong last item" << endl
             << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
        isError = true;
    } else {
        cout << "Success: ArraySequence::GetLast(); Correct last item" << endl;
    }
}

void ArraySequenceTester::TestGet() {
    bool isError = false;

    ArraySequence<char> *asCharEmpty = new ArraySequence<char>(this->dummyCharArrLen);
    try {
        asCharEmpty->Get(1);
        isError = true;
    } catch (...) {
        cout << "Success: ArraySequence::Get(int index); Item of empty arrayseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ArraySequence::Get(int index); Item of empty arrayseq was gotten" << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = asChar->Get(i);

        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence::Get(int index); Wrong index item" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
            isError = true;
            break;
        }
    }
    if (!isError) {
        cout << "Success: ArraySequence::Get(int index); Correct index item" << endl;
    }
}

void ArraySequenceTester::TestGetSubsequence() {
    bool isError = false;

    ArraySequence<char> *asCharEmpty = new ArraySequence<char>(this->dummyCharArrLen);
    try {
        asCharEmpty->GetSubsequence(0, 1);
        isError = true;
    } catch (...) {
        cout
                << "Success: ArraySequence::GetSubsequence(int start_index, int end_index); Subseq from empty arrayseq was not gotten"
                << endl;
    }

    if (isError) {
        cout
                << "Error: ArraySequence::GetSubsequence(int start_index, int end_index); Subseq from empty arrayseq was gotten"
                << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    try {
        asChar->GetSubsequence(-1, 100);
        isError = true;
    } catch (...) {
        cout
                << "Success: ArraySequence::GetSubsequence(int start_index, int end_index); Subseq with incorrect borders was not gotten"
                << endl;
    }

    if (isError) {
        cout
                << "Error: ArraySequence::GetSubsequence(int start_index, int end_index); Subseq with incorrect borders was gotten"
                << endl;
    }

    isError = false;

    int start_index = 0;
    int end_index = 1;
    ArraySequence<char> *subArr = new ArraySequence<char>(*(asChar->GetSubsequence(start_index, end_index)));
    for (int i = start_index; i < end_index; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = subArr->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence::GetSubsequence(int start_index, int end_index); Subseq is incorrect"
                 << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence::GetSubsequence(int start_index, int end_index); Subseq is correct" << endl;
    }
}

void ArraySequenceTester::TestPrepend() {
    bool isError = false;

    ArraySequence<char> *asCharEmpty = new ArraySequence<char>(this->dummyCharArrLen);

    char expectedItem = 'z';
    asCharEmpty->Prepend(expectedItem);

    char receivedItem = asCharEmpty->GetFirst();
    int receivedLen = asCharEmpty->GetLength();
    if (expectedItem != receivedItem || receivedLen != this->dummyCharArrLen + 1) {
        cout << "Error: ArraySequence::Prepend(T item); Prepended char to empty arrayseq" << endl
             << "Expected: " << expectedItem << " Received: " << receivedItem << endl
             << " Received length " << receivedLen << endl;

        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::Prepend(T item); Prepended char to empty arrayseq" << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->Prepend('z');

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = asChar->Get(i);

            if (i == 0) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i - 1];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::Prepend(T item); Prepended char to arrayseq" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::Prepend(T item); Prepended char to empty arrayseq" << endl
             << "Length error" << endl;
    }

    if (!isError) {
        cout << "Success: ArraySequence::Prepend(T item); Prepended char to arrayseq" << endl;
    }
}

void ArraySequenceTester::TestAppend() {
    bool isError = false;

    ArraySequence<char> *asCharEmpty = new ArraySequence<char>(this->dummyCharArrLen);

    char expectedItem = 'z';
    asCharEmpty->Append(expectedItem);

    char receivedItem = asCharEmpty->GetLast();
    int receivedLen = asCharEmpty->GetLength();
    if (expectedItem != receivedItem || receivedLen != this->dummyCharArrLen + 1) {
        cout << "Error: ArraySequence::Append(T item); Appended char to empty arrayseq" << endl
             << "Expected: " << expectedItem << " Received " << receivedItem << " Expected length " << receivedLen
             << endl;

        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::Append(T item); Appended char to empty arrayseq" << endl;
    }

    isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->Append('z');

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = asChar->Get(i);

            if (i == expectedLen - 1) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::Append(T item); Appended char to arrayseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::Append(T item); Appended char to empty arrayseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::Append(T item); Appended char to arrayseq" << endl;
    }
}

void ArraySequenceTester::TestInsertAt() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->InsertAt('z', 1);

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = asChar->Get(i);

            if (i < 1) {
                expectedItem = this->dummyCharArr[i];
            } else if (i == 1) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i - 1];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::InsertAt(T item, int index); Inserted char to arrayseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::InsertAt(T item, int index); Inserted char to arrayseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::InsertAt(T item, int index); Inserted char to arrayseq" << endl;
    }
}

void ArraySequenceTester::TestRemoveAt() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->RemoveAt(1);

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = asChar->Get(i);

            if (i < 1) {
                expectedItem = this->dummyCharArr[i];
            } else if (i >= 1) {
                expectedItem = this->dummyCharArr[i + 1];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::RemoveAt(int index); Removed char at index of arrayseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::RemoveAt(int index); Removed char at index of arrayseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::RemoveAt(int index); Removed char at index of arrayseq" << endl;
    }
}

void ArraySequenceTester::TestRemove() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->Remove('a');

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = asChar->Get(i);

            expectedItem = this->dummyCharArr[i + 1];
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::Remove(T value); Removed char by its value of arrayseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::Remove(T value); Removed char by its value of arrayseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::Remove(T value); Removed char by its value of arrayseq" << endl;
    }
}

void ArraySequenceTester::TestRemoveAll() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->RemoveAll('a');

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = asChar->Get(i);

            expectedItem = this->dummyCharArr[i + 1];
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::RemoveAll(T value); Removed all chars by its value of arrayseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::RemoveAll(T value); Removed all chars by its value of arrayseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::RemoveAll(T value); Removed all chars by its value of arrayseq" << endl;
    }
}

void ArraySequenceTester::TestConcat() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ArraySequence<char>* asChar1 = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    ArraySequence<char>* asChar2 = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);

    Sequence<char> *concatedSeq = asChar1->Concat(asChar2);

    int expectedLen = this->dummyCharArrLen * 2;
    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = concatedSeq->Get(i);

            expectedItem = this->dummyCharArr[i % 3];
            if (expectedItem != receivedItem) {
                cout << "Error: ArraySequence::Concat(ArraySequence<T> *array); Concated 2 same arrayseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ArraySequence::Concat(ArraySequence<T> *array); Concated 2 same arrayseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ArraySequence::Concat(ArraySequence<T> *array); Concated 2 same arrayseq" << endl;
    }
}

void ArraySequenceTester::TestCopy() {
    bool isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    Sequence<char> *sCharCopied = asChar->Copy();

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = sCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence::Copy();" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ArraySequence::Copy();" << endl;
    }

    isError = false;

    asChar->Prepend('z');

    if (asChar->Get(0) == sCharCopied->Get(0)) {
        cout << "Error: ArraySequence::Copy(); trying to change source ArraySequence"
             << endl << "Copied array changes after changing of source" << endl;
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: ArraySequence::Copy(); trying to change source ArraySequence"
                << endl;
    }

}

void ArraySequenceTester::TestSet() {
    bool isError = false;

    ArraySequence<char> *asChar = new ArraySequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    asChar->Set('z', 1);

    char* newDummyCharArr = this->dummyCharArr;
    newDummyCharArr[1] = 'z';

    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = newDummyCharArr[i];
        char receivedItem = asChar->Get(i);

        if (expectedItem != receivedItem) {
            cout << "Error: ArraySequence::Set(T value, const int index); Changed ArrSeq is wrong" << endl
                 << "Expected: " << expectedItem << " Received " << receivedItem << endl;

            isError = true;
            return;
        }

    }

    if (!isError) {
        cout << "Success: ArraySequence::Set(T value, const int index); Changed ArrSeq is correct" << endl;
    }
}
