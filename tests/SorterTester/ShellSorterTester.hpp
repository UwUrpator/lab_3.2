#pragma once

#include <iostream>

#include "../tests/Informator/Informator.hpp"
#include "../source/Sequence/Sequence.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/ListSequence/ListSequence.hpp"
#include "../source/Sorter/ShellSorter.hpp"

using namespace std;

class ShellSorterTester {
private:
    int *dummyIntArr;
    int dummyIntArrLen;

    Sequence<int>* dummySeqArr;
    Sequence<int>* dummySeqList;

public:
    ShellSorterTester();

    void TestArrSeqSort();
    void TestListSeqSort();
};

ShellSorterTester::ShellSorterTester() {
    this->dummyIntArrLen = 6;

    this->dummyIntArr = static_cast<int *>(operator new[](this->dummyIntArrLen * sizeof(int)));

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

void ShellSorterTester::TestArrSeqSort() {
    ShellSorter<int>* ssorter = new ShellSorter<int>();

    Sequence<int>* copiedSeq = this->dummySeqArr->Copy();

    Sequence<int>* copiedSeqSorted = ssorter->Sort(copiedSeq, [](int a, int b) -> int { return a - b; });

    Informator(
            (
                    copiedSeqSorted->Get(0) == -2 &&
                    copiedSeqSorted->Get(1) == -1 &&
                    copiedSeqSorted->Get(2) == 0 &&
                    copiedSeqSorted->Get(3) == 3 &&
                    copiedSeqSorted->Get(4) == 3 &&
                    copiedSeqSorted->Get(5) == 4
            ),
            "Success: Sequence<T>* ShellSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); passed ArraySequence",
            "Error: Sequence<T>* ShellSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); sorted incorrectly, passed ArraySequence"
    );
}

void ShellSorterTester::TestListSeqSort() {
    ShellSorter<int>* ssorter = new ShellSorter<int>();

    Sequence<int>* copiedSeq = this->dummySeqList->Copy();

    Sequence<int>* copiedSeqSorted = ssorter->Sort(copiedSeq, [](int a, int b) -> int { return a - b; });

    Informator(
            (
                    copiedSeqSorted->Get(0) == -2 &&
                    copiedSeqSorted->Get(1) == -1 &&
                    copiedSeqSorted->Get(2) == 0 &&
                    copiedSeqSorted->Get(3) == 3 &&
                    copiedSeqSorted->Get(4) == 3 &&
                    copiedSeqSorted->Get(5) == 4
            ),
            "Success: Sequence<T>* ShellSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); passed ListSequence",
            "Error: Sequence<T>* ShellSorter<T>::Sort(Sequence<T>* sequence, int (*comparator)(T, T)); sorted incorrectly, passed ListSequence"
    );
}
