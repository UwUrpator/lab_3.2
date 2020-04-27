#pragma once

#include <iostream>
#include "../source/LinkedList/LinkedList.hpp"
#include "../source/ListSequence/ListSequence.hpp"
#include "../DummyClass/DummyClass.hpp"
#include "../source/Sequence/Sequence.hpp"

using namespace std;

class ListSequenceTester {
private:
    char *dummyCharArr;
    int dummyCharArrLen;

    DummyClass *dummyClassArr;
    int dummyClassArrLen;
public:
    ListSequenceTester();

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
};

ListSequenceTester::ListSequenceTester() {
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
}

void ListSequenceTester::TestConstructor1() {
    bool isError = false;
    try {
        ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, 0);
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence(T *items, int size); passed: dummyCharArr, 0" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence(T *items, int size); passed: dummyCharArr, 0" << endl
             << "Not empty list of 0 length was created" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = lsChar->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence(T *items, int size); passed: dummyCharArr, dummyCharArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence(T *items, int size); passed: dummyCharArr, dummyCharArrLen" << endl;
    }

    isError = false;

    ListSequence<DummyClass> *lsClass = new ListSequence<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    for (int i = 0; i < this->dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = lsClass->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence(T *items, int size); passed: dummyClassArr, dummyClassArrLen" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence(T *items, int size); passed: dummyClassArr, dummyClassArrLen" << endl;
    }
}

void ListSequenceTester::TestConstructor2() {
    bool isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>();
    try {
        lsChar->GetFirst();
        isError = true;
    } catch (...) {}

    try {
        lsChar->GetLast();
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence(); New list is empty" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence(); New list is not empty" << endl;
    }
}

void ListSequenceTester::TestConstructor3() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();
    try {
        ListSequence<char> *lsEmpty = new ListSequence<char>(*lsCharEmpty);
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence(const ListSequence<T> &list); passed: lsCharEmpty (empty list)" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence(const ListSequence<T> &list); passed: lsCharEmpty (empty list)" << endl
             << "Empty list was copied";
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    ListSequence<char> *lsCharCopied = new ListSequence<char>(*lsChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = lsCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence(const ListSequence<T> &list); passed: lsChar (list of chars)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence(const ListSequence<T> &list); passed: lsChar (list of chars)" << endl;
    }

    isError = false;

    lsChar->InsertAt('z', 0);

    if (lsChar->Get(0) == lsCharCopied->Get(0)) {
        cout << "Error: ListSequence(const ListSequence<T> &list); trying to change source ListSequence (list of chars)"
             << endl << "Copied list changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: ListSequence(const ListSequence<T> &list); trying to change source ListSequence (list of chars)"
                << endl;
    }

    isError = false;

    ListSequence<DummyClass> *lsClass = new ListSequence<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    ListSequence<DummyClass> *lsClassCopied = new ListSequence<DummyClass>(*lsClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = lsClassCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence(const ListSequence<T> &list); passed: lsClass (list of DummyClass)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence(const ListSequence<T> &list); passed: lsClass (list of DummyClass)" << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(456));
    lsClass = new ListSequence<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = lsClass->Get(0);
    DummyClass firstCopied = lsClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout
                << "Error: ListSequence(const ListSequence<T> &list); trying to change source ListSequence (list of DummyClass)"
                << endl << "Copied list changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout
                << "Success: ListSequence(const ListSequence<T> &list); trying to change source ListSequence (list of chars)"
                << endl;
    }
}

void ListSequenceTester::TestConstructor4() {
    bool isError = false;


    Sequence<char> *sCharEmpty = new ListSequence<char>();
    try {
        ListSequence<char> *lsEmpty = new ListSequence<char>(*sCharEmpty);
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence(const Sequence<T> &list); passed: sCharEmpty (empty seq)" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence(const Sequence<T> &list); passed: sCharEmpty (empty seq)" << endl
             << "Empty list was copied";
    }

    isError = false;

    Sequence<char> *sChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    ListSequence<char> *lsCharCopied = new ListSequence<char>(*sChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = lsCharCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence(const Sequence<T> &list); passed: sChar (seq of chars)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence(const Sequence<T> &list); passed: sChar (seq of chars)" << endl;
    }

    isError = false;

    sChar->InsertAt('z', 0);

    if (sChar->Get(0) == lsCharCopied->Get(0)) {
        cout << "Error: ListSequence(const Sequence<T> &list); trying to change source Sequence (seq of chars)"
             << endl << "Copied list changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence(const Sequence<T> &list); trying to change source Sequence (seq of chars)"
             << endl;
    }

    isError = false;

    Sequence<DummyClass> *sClass = new ListSequence<DummyClass>(this->dummyClassArr, this->dummyClassArrLen);
    ListSequence<DummyClass> *lsClassCopied = new ListSequence<DummyClass>(*sClass);

    for (int i = 0; i < dummyClassArrLen; ++i) {
        DummyClass expectedItem = this->dummyClassArr[i];
        DummyClass receivedItem = lsClassCopied->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence(const Sequence<T> &list); passed: sClass (seq of DummyClass)" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence(const Sequence<T> &list); passed: sClass (seq of DummyClass)" << endl;
    }

    isError = false;

    DummyClass *newArr = this->dummyClassArr;
    newArr[0] = *(new DummyClass(789));
    sClass = new ListSequence<DummyClass>(newArr, this->dummyClassArrLen);

    DummyClass firstSource = sClass->Get(0);
    DummyClass firstCopied = lsClassCopied->Get(0);

    if (firstSource == firstCopied) {
        cout << "Error: ListSequence(const Sequence<T> &list); trying to change source Sequence (seq of DummyClass)"
             << endl << "Copied list changes after changing of source";
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence(const Sequence<T> &list); trying to change source Sequence (seq of chars)"
             << endl;
    }
}

void ListSequenceTester::TestGetLength() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();
    try {
        lsCharEmpty->GetLength();
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence::TestGetLength(); Length of empty listseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence::TestGetLength(); Length of empty listseq was gotten" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);

    int expectedLen = this->dummyCharArrLen;
    int receivedLen = lsChar->GetLength();

    if (expectedLen != receivedLen) {
        cout << "Error: ListSequence::TestGetLength(); Length of listseq is incorrect" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::TestGetLength(); Length of listseq is correct" << endl;
    }

}

void ListSequenceTester::TestGetFirst() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();
    try {
        lsCharEmpty->GetFirst();
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence::GetFirst(); First item of empty listseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence::GetFirst(); First item of empty listseq was gotten" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyClassArrLen);
    char expectedItem = this->dummyCharArr[0];
    char receivedItem = lsChar->GetFirst();

    if (expectedItem != receivedItem) {
        cout << "Error: ListSequence::GetFirst(); Wrong first item" << endl
             << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
        isError = true;
    } else {
        cout << "Success: ListSequence::GetFirst(); Correct first item" << endl;
    }

}

void ListSequenceTester::TestGetLast() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();
    try {
        lsCharEmpty->GetLast();
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence::GetLast(); Last item of empty listseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence::GetLast(); Last item of empty listseq was gotten" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    char expectedItem = this->dummyCharArr[this->dummyCharArrLen - 1];
    char receivedItem = lsChar->GetLast();

    if (expectedItem != receivedItem) {
        cout << "Error: ListSequence::GetLast(); Wrong last item" << endl
             << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
        isError = true;
    } else {
        cout << "Success: ListSequence::GetLast(); Correct last item" << endl;
    }
}

void ListSequenceTester::TestGet() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();
    try {
        lsCharEmpty->Get(1);
        isError = true;
    } catch (...) {
        cout << "Success: ListSequence::Get(int index); Item of empty listseq was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: ListSequence::Get(int index); Item of empty listseq was gotten" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = lsChar->Get(i);

        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence::Get(int index); Wrong index item" << endl
                 << "Expected: " << expectedItem << " Received: " << receivedItem << endl;
            isError = true;
            break;
        }
    }
    if (!isError) {
        cout << "Success: ListSequence::Get(int index); Correct index item" << endl;
    }
}

void ListSequenceTester::TestGetSubsequence() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();
    try {
        lsCharEmpty->GetSubsequence(0, 1);
        isError = true;
    } catch (...) {
        cout
                << "Success: ListSequence::GetSubsequence(int start_index, int end_index); Subseq from empty listseq was not gotten"
                << endl;
    }

    if (isError) {
        cout
                << "Error: ListSequence::GetSubsequence(int start_index, int end_index); Subseq from empty listseq was gotten"
                << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    try {
        lsChar->GetSubsequence(-1, 100);
        isError = true;
    } catch (...) {
        cout
                << "Success: ListSequence::GetSubsequence(int start_index, int end_index); Subseq with incorrect borders was not gotten"
                << endl;
    }

    if (isError) {
        cout
                << "Error: ListSequence::GetSubsequence(int start_index, int end_index); Subseq with incorrect borders was gotten"
                << endl;
    }

    isError = false;

    int start_index = 0;
    int end_index = 1;
    ListSequence<char> *subList = new ListSequence<char>(*(lsChar->GetSubsequence(start_index, end_index)));
    for (int i = start_index; i < end_index; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char receivedItem = subList->Get(i);
        if (expectedItem != receivedItem) {
            cout << "Error: ListSequence::GetSubsequence(int start_index, int end_index); Subseq is incorrect"
                 << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: ListSequence::GetSubsequence(int start_index, int end_index); Subseq is correct" << endl;
    }
}

void ListSequenceTester::TestPrepend() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();

    char expectedItem = 'z';
    lsCharEmpty->Prepend(expectedItem);

    char receivedItem = lsCharEmpty->GetFirst();
    int receivedLen = lsCharEmpty->GetLength();
    if (expectedItem != receivedItem || receivedLen != 1) {
        cout << "Error: ListSequence::Prepend(T item); Prepended char to empty listseq" << endl
             << "Expected: " << expectedItem << " Received: " << receivedItem << " Expected length " << receivedLen << endl;

        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::Prepend(T item); Prepended char to empty listseq" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    lsChar->Prepend('z');

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar->Get(i);

            if (i == 0) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i - 1];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::Prepend(T item); Prepended char to listseq" << endl
                     << "Expected: " << expectedItem << " Received: " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::Prepend(T item); Prepended char to empty listseq" << endl
             << "Length error" << endl;
    }

    if (!isError) {
        cout << "Success: ListSequence::Prepend(T item); Prepended char to listseq" << endl;
    }
}

void ListSequenceTester::TestAppend() {
    bool isError = false;

    ListSequence<char> *lsCharEmpty = new ListSequence<char>();

    char expectedItem = 'z';
    lsCharEmpty->Append(expectedItem);

    char receivedItem = lsCharEmpty->GetFirst();
    int receivedLen = lsCharEmpty->GetLength();
    if (expectedItem != receivedItem || receivedLen != 1) {
        cout << "Error: ListSequence::Append(T item); Appended char to empty listseq" << endl
             << "Expected: " << expectedItem << " Received " << receivedItem << " Expected length " << receivedLen << endl;

        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::Append(T item); Appended char to empty listseq" << endl;
    }

    isError = false;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    lsChar->Append('z');

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar->Get(i);

            if (i == expectedLen - 1) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::Append(T item); Appended char to listseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::Append(T item); Appended char to empty listseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::Append(T item); Appended char to listseq" << endl;
    }
}

void ListSequenceTester::TestInsertAt() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    lsChar->InsertAt('z', 1);

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar->Get(i);

            if (i < 1) {
                expectedItem = this->dummyCharArr[i];
            } else if (i == 1) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i - 1];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::InsertAt(T item, int index); Inserted char to listseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::InsertAt(T item, int index); Inserted char to listseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::InsertAt(T item, int index); Inserted char to listseq" << endl;
    }
}

void ListSequenceTester::TestRemoveAt() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    lsChar->RemoveAt(1);

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar->Get(i);

            if (i < 1) {
                expectedItem = this->dummyCharArr[i];
            } else if (i >= 1) {
                expectedItem = this->dummyCharArr[i+1];
            }
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::RemoveAt(int index); Removed char at index of listseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::RemoveAt(int index); Removed char at index of listseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::RemoveAt(int index); Removed char at index of listseq" << endl;
    }
}

void ListSequenceTester::TestRemove() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    lsChar->Remove('a');

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar->Get(i);

            expectedItem = this->dummyCharArr[i+1];
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::Remove(T value); Removed char by its value of listseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::Remove(T value); Removed char by its value of listseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::Remove(T value); Removed char by its value of listseq" << endl;
    }
}

void ListSequenceTester::TestRemoveAll() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ListSequence<char> *lsChar = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    lsChar->RemoveAll('a');

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar->Get(i);

            expectedItem = this->dummyCharArr[i+1];
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::RemoveAll(T value); Removed all chars by its value of listseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::RemoveAll(T value); Removed all chars by its value of listseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::RemoveAll(T value); Removed all chars by its value of listseq" << endl;
    }
}

void ListSequenceTester::TestConcat() {
    bool isError = false;

    char receivedItem;
    char expectedItem;

    ListSequence<char>* lsChar1 = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);
    ListSequence<char>* lsChar2 = new ListSequence<char>(this->dummyCharArr, this->dummyCharArrLen);

    lsChar1 = new ListSequence<char>(*(lsChar1->Concat(lsChar2)));

    int expectedLen = this->dummyCharArrLen * 2;
    try {
        for (int i = 0; i < expectedLen; ++i) {
            receivedItem = lsChar1->Get(i);

            expectedItem = this->dummyCharArr[i % 3];
            if (expectedItem != receivedItem) {
                cout << "Error: ListSequence::Concat(ListSequence<T> *list); Concated 2 same listseq" << endl
                     << "Expected: " << expectedItem << " Received " << receivedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: ListSequence::Concat(ListSequence<T> *list); Concated 2 same listseq" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: ListSequence::Concat(ListSequence<T> *list); Concated 2 same listseq" << endl;
    }
}
