#pragma once

#include <iostream>

#include "../tests/Informator/Informator.hpp"
#include "../source/Sequence/Sequence.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/ListSequence/ListSequence.hpp"
#include "../source/Sorter/QuickSorter.hpp"

using namespace std;

class QuickSorterTester {
private:
    int *dummyIntArr;
    int dummyIntArrLen;

    Sequence<int>* dummySeqArr;
    Sequence<int>* dummySeqList;

public:
    QuickSorterTester();

    void TestArrSeqSort();
    void TestListSeqSort();
};

QuickSorterTester::QuickSorterTester() {
    this->dummyIntArrLen = 6;

    this->dummyIntArr[0] = -1;
    this->dummyIntArr[1] = 3;
    this->dummyIntArr[2] = -2;
    this->dummyIntArr[3] = 0;
    this->dummyIntArr[4] = 3;
    this->dummyIntArr[5] = 4;

    this->dummySeqArr = new ArraySequence<int>(this->dummyIntArr, this->dummyIntArrLen);
    this->dummySeqList = new ListSequence<int>(this->dummyIntArr, this->dummyIntArrLen);

    this->TestArrSeqSort();
    this->TestListSeqSort();
}

void QuickSorterTester::TestArrSeqSort() {
    QuickSorter<int>* qsorter = new QuickSorter<int>();

    Sequence<int>* copiedSeq = this->dummySeqArr->Copy();

    Sequence<int>* copiedSeqSorted = qsorter->Sort(copiedSeq, [](int a, int b) -> int { return a - b; });

    Informator(
            (
                    copiedSeqSorted->Get(0) == -2 &&
            copiedSeqSorted->Get(1) == -1 &&
            copiedSeqSorted->Get(2) == 0 &&
            copiedSeqSorted->Get(3) == 3 &&
            copiedSeqSorted->Get(4) == 3 &&
            copiedSeqSorted->Get(5) == 4
    ),
    "Success: Sequence<T>* QuickSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); passed ArraySequence",
    "Error: Sequence<T>* QuickSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); sorted incorrectly, passed ArraySequence"
    );
}

void QuickSorterTester::TestListSeqSort() {
    QuickSorter<int>* qsorter = new QuickSorter<int>();

    Sequence<int>* copiedSeq = this->dummySeqList->Copy();

    Sequence<int>* copiedSeqSorted = qsorter->Sort(copiedSeq, [](int a, int b) -> int { return a - b; });

    Informator(
            (
                    copiedSeqSorted->Get(0) == -2 &&
                    copiedSeqSorted->Get(1) == -1 &&
                    copiedSeqSorted->Get(2) == 0 &&
                    copiedSeqSorted->Get(3) == 3 &&
                    copiedSeqSorted->Get(4) == 3 &&
                    copiedSeqSorted->Get(5) == 4
            ),
            "Success: Sequence<T>* QuickSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); passed ListSequence",
            "Error: Sequence<T>* QuickSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); sorted incorrectly, passed ListSequence"
    );
}