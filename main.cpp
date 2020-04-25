#include <iostream>
#include "source/DynamicArray/DynamicArray.hpp"

using namespace std;

int main() {
    char arr1[3] = {'a', 'b', 'c'};
    char arr2[4] = {'a', 'b', 'c', 'd'};
    char arr3[5] = {'a', 'a', 'b', 'a', 'a'};
    int arri1[4] = {1, 2, 3, 4};

    //ListSequence<char>* lseq1 = new ListSequence<char>(arr1, 3);
    //ListSequence<char>* lseq2 = new ListSequence<char>(arr2, 4);

    DynamicArray<char>* darr1 = new DynamicArray<char>(arr1, 3);

    //cout << (*darr1)[0];

    /*llist2 = llist2->Concat(llist1);

    cout << llist2->GetIndex(6);

    Sequence<char>* seq = lseq2->Concat(lseq1);

    cout << seq->Get(6);*/

    //Sequence<char>* seq = new ListSequence<char>(arr1, 3);
    /*ArraySequence<char>* arrSeq = new ArraySequence<char>(*seq);

    cout << "Check seq -> arrSeq" << endl;
    cout << "Expected: " << seq->GetLast() << " Reality: " << arrSeq->GetLast();*/

    //ListSequence<char>* listSeq = new ListSequence<char>(*seq);

    /*cout << "Check seq -> arrSeq" << endl;
    cout << "Expected: " << seq->GetLast() << " Reality: " << listSeq->GetLast();*/

    return 0;
}
