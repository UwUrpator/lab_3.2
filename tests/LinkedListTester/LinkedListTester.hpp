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

    void TestGetFirst();

    void TestGetLast();

    void TestGet();

    void TestGetSubList();

    void TestGetLength();

    void TestPrepend();

    void TestAppend();

    void TestInsertAt();

    void TestRemoveAt();

    void TestRemove();

    void TestRemoveAll();

    void TestConcat();
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

    TestGetFirst();
    TestGetLast();
    TestGet();
    TestGetSubList();
    TestGetLength();

    TestPrepend();
    TestAppend();
    TestInsertAt();

    TestRemoveAt();
    TestRemove();
    TestRemoveAll();
    TestConcat();
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

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();
    try {
        LinkedList<char> *llistEmpty = new LinkedList<char>(*llistCharEmpty);
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList(const LinkedList<T> &list); passed: llistCharEmpty (empty list)" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList(const LinkedList<T> &list); passed: llistCharEmpty (empty list)" << endl
             << "Empty list was copied";
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    LinkedList<char> *llistCharCopied = new LinkedList<char>(*llistChar);

    for (int i = 0; i < dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = llistCharCopied->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList(const LinkedList<T> &list); passed: llistChar (list of chars)" << endl
                 << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;

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

void LinkedListTester::TestGetFirst() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();
    try {
        llistCharEmpty->GetFirst();
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList::GetFirst(); First item of empty list was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList::GetFirst(); First item of empty list was gotten" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyClassArrLen);
    char expectedItem = this->dummyCharArr[0];
    char recievedItem = llistChar->GetFirst();

    if (expectedItem != recievedItem) {
        cout << "Error: LinkedList::GetFirst(); Wrong first item" << endl
             << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;
        isError = true;
    } else {
        cout << "Success: LinkedList::GetFirst(); Correct first item" << endl;
    }
}

void LinkedListTester::TestGetLast() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();
    try {
        llistCharEmpty->GetLast();
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList::GetLast(); Last item of empty list was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList::GetLast(); Last item of empty list was gotten" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    char expectedItem = this->dummyCharArr[this->dummyCharArrLen - 1];
    char recievedItem = llistChar->GetLast();

    if (expectedItem != recievedItem) {
        cout << "Error: LinkedList::GetLast(); Wrong last item" << endl
             << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;
        isError = true;
    } else {
        cout << "Success: LinkedList::GetLast(); Correct last item" << endl;
    }
}

void LinkedListTester::TestGet() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();
    try {
        llistCharEmpty->Get(1);
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList::Get(int index); Item of empty list was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList::Get(int index); Item of empty list was gotten" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    for (int i = 0; i < this->dummyCharArrLen; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = llistChar->Get(i);

        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList::Get(int index); Wrong index item" << endl
                 << "Expected: " << expectedItem << " Recieved: " << recievedItem << endl;
            isError = true;
            break;
        }
    }
    if (!isError) {
        cout << "Success: LinkedList::Get(int index); Correct index item" << endl;
    }
}

void LinkedListTester::TestGetSubList() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();
    try {
        llistCharEmpty->GetSubList(0, 1);
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList::GetSubList(int start_index, int end_index); Sublist from empty list was not gotten"
             << endl;
    }

    if (isError) {
        cout << "Error: LinkedList::GetSubList(int start_index, int end_index); Sublist from empty list was gotten"
             << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    try {
        llistChar->GetSubList(-1, 100);
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList::GetSubList(int start_index, int end_index); Sublist with incorrect borders was not gotten"
             << endl;
    }

    if (isError) {
        cout << "Error: LinkedList::GetSubList(int start_index, int end_index); Sublist with incorrect borders was gotten"
             << endl;
    }

    isError = false;

    int start_index = 0;
    int end_index = 1;
    LinkedList<char> *subList = llistChar->GetSubList(start_index, end_index);
    for (int i = start_index; i < end_index; ++i) {
        char expectedItem = this->dummyCharArr[i];
        char recievedItem = subList->Get(i);
        if (expectedItem != recievedItem) {
            cout << "Error: LinkedList::GetSubList(int start_index, int end_index); Sublist is incorrect" << endl;

            isError = true;
            break;
        }
    }

    if (!isError) {
        cout << "Success: LinkedList::GetSubList(int start_index, int end_index); Sublist is correct" << endl;
    }
}

void LinkedListTester::TestGetLength() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();
    try {
        llistCharEmpty->GetLength();
        isError = true;
    } catch (...) {
        cout << "Success: LinkedList::TestGetLength(); Length of empty list was not gotten" << endl;
    }

    if (isError) {
        cout << "Error: LinkedList::TestGetLength(); Length of empty list was gotten" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);

    int expectedLen = this->dummyCharArrLen;
    int recievedLen = llistChar->GetLength();

    if (expectedLen != recievedLen) {
        cout << "Error: LinkedList::TestGetLength(); Length of list is incorrect" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::TestGetLength(); Length of list is correct" << endl;
    }

}

void LinkedListTester::TestPrepend() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();

    char expectedItem = 'z';
    llistCharEmpty->Prepend(expectedItem);

    char recievedItem = llistCharEmpty->GetFirst();
    int recievedLen = llistCharEmpty->GetLength();
    if (expectedItem != recievedItem || recievedLen != 1) {
        cout << "Error: LinkedList::Prepend(T item); Prepended char to empty list" << endl
             << "Expected: " << expectedItem << " Recieved " << recievedItem << " Expected length " << recievedLen << endl;

        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::Prepend(T item); Prepended char to empty list" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    llistChar->Prepend('z');

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar->Get(i);

            if (i == 0) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i - 1];
            }
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::Prepend(T item); Prepended char to list" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::Prepend(T item); Prepended char to empty list" << endl
             << "Length error" << endl;
    }

    if (!isError) {
        cout << "Success: LinkedList::Prepend(T item); Prepended char to list" << endl;
    }
}

void LinkedListTester::TestAppend() {
    bool isError = false;

    LinkedList<char> *llistCharEmpty = new LinkedList<char>();

    char expectedItem = 'z';
    llistCharEmpty->Append(expectedItem);

    char recievedItem = llistCharEmpty->GetFirst();
    int recievedLen = llistCharEmpty->GetLength();
    if (expectedItem != recievedItem || recievedLen != 1) {
        cout << "Error: LinkedList::Append(T item); Appended char to empty list" << endl
             << "Expected: " << expectedItem << " Recieved " << recievedItem << " Expected length " << recievedLen << endl;

        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::Append(T item); Appended char to empty list" << endl;
    }

    isError = false;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    llistChar->Append('z');

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar->Get(i);

            if (i == expectedLen - 1) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i];
            }
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::Append(T item); Appended char to list" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::Append(T item); Appended char to empty list" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::Append(T item); Appended char to list" << endl;
    }
}

void LinkedListTester::TestInsertAt() {
    bool isError = false;

    char recievedItem;
    char expectedItem;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    llistChar->InsertAt('z', 1);

    int expectedLen = this->dummyCharArrLen + 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar->Get(i);

            if (i < 1) {
                expectedItem = this->dummyCharArr[i];
            } else if (i == 1) {
                expectedItem = 'z';
            } else {
                expectedItem = this->dummyCharArr[i - 1];
            }
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::InsertAt(T item, int index); Inserted char to list" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::InsertAt(T item, int index); Inserted char to list" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::InsertAt(T item, int index); Inserted char to list" << endl;
    }

}

void LinkedListTester::TestRemoveAt() {
    bool isError = false;

    char recievedItem;
    char expectedItem;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    llistChar->RemoveAt(1);

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar->Get(i);

            if (i < 1) {
                expectedItem = this->dummyCharArr[i];
            } else if (i >= 1) {
                expectedItem = this->dummyCharArr[i+1];
            }
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::RemoveAt(int index); Removed char at index of list" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::RemoveAt(int index); Removed char at index of list" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::RemoveAt(int index); Removed char at index of list" << endl;
    }

}

void LinkedListTester::TestRemove() {
    bool isError = false;

    char recievedItem;
    char expectedItem;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    llistChar->Remove('a');

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar->Get(i);

            expectedItem = this->dummyCharArr[i+1];
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::Remove(T value); Removed char by its value of list" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::Remove(T value); Removed char by its value of list" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::Remove(T value); Removed char by its value of list" << endl;
    }
}

void LinkedListTester::TestRemoveAll() {
    bool isError = false;

    char recievedItem;
    char expectedItem;

    LinkedList<char> *llistChar = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    llistChar->RemoveAll('a');

    int expectedLen = this->dummyCharArrLen - 1;

    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar->Get(i);

            expectedItem = this->dummyCharArr[i+1];
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::RemoveAll(T value); Removed all chars by its value of list" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::RemoveAll(T value); Removed all chars by its value of list" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::RemoveAll(T value); Removed all chars by its value of list" << endl;
    }
}

void LinkedListTester::TestConcat() {
    bool isError = false;

    char recievedItem;
    char expectedItem;

    LinkedList<char>* llistChar1 = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);
    LinkedList<char>* llistChar2 = new LinkedList<char>(this->dummyCharArr, this->dummyCharArrLen);

    llistChar1 = llistChar1->Concat(llistChar2);

    int expectedLen = this->dummyCharArrLen * 2;
    try {
        for (int i = 0; i < expectedLen; ++i) {
            recievedItem = llistChar1->Get(i);

            expectedItem = this->dummyCharArr[i % 3];
            if (expectedItem != recievedItem) {
                cout << "Error: LinkedList::Concat(LinkedList<T> *list); Concated 2 same lists" << endl
                     << "Expected: " << expectedItem << " Recieved " << recievedItem << endl;

                isError = true;
                return;
            }
        }
    } catch (...) {
        cout << "Error: LinkedList::Concat(LinkedList<T> *list); Concated 2 same lists" << endl
             << "Length error" << endl;
        isError = true;
    }

    if (!isError) {
        cout << "Success: LinkedList::Concat(LinkedList<T> *list); Concated 2 same lists" << endl;
    }
}
