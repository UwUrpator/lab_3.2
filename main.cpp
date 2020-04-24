#include <iostream>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "ArraySequence.hpp"
#include "LinearForm.hpp"

using namespace std;

int main() {
    char arr[3] = {'a', 'b', 'c'};
    char arr2[4] = {'a', 'b', 'c', 'd'};
    char arr3[5] = {'a', 'a', 'b', 'a', 'a'};
    int arri1[4] = {1, 2, 3, 4};
    DynamicArray<char>* darr = new DynamicArray<char>(arr, 3);

    ArraySequence<char>* arrSeq = new ArraySequence<char>(arr, 3);

    /*cout << "ArraySeq GetFirst" << endl;
    cout << arrSeq->GetFirst() << endl;

    cout << "ArraySeq GetLast" << endl;
    cout << arrSeq->GetLast() << endl;

    cout << "ArraySeq Get" << endl;
    cout << arrSeq->Get(1) << endl;

    cout << "ArraySeq Prepend" << endl;
    arrSeq->Prepend('z');
    cout << arrSeq->GetFirst() << endl;

    cout << "ArraySeq Append" << endl;
    arrSeq->Append('z');
    cout << arrSeq->GetLast() << endl;

    cout << "ArraySeq InsertAt" << endl;
    arrSeq->InsertAt(1, 'z');
    cout << arrSeq->Get(1) << endl;

    arrSeq = new ArraySequence<char>(arr, 3);
    cout << "ArraySeq GetSubSeq" << endl;
    Sequence<char>* subSeq = arrSeq->GetSubsequence(1, 3);
    cout << subSeq->GetFirst() << subSeq->GetLast() << endl;

    cout << "ArraySeq RemoveAt" << endl;
    arrSeq->RemoveAt(1);
    cout << arrSeq->GetFirst() << arrSeq->Get(1) << arrSeq->GetLast() << endl;

    arrSeq = new ArraySequence<char>(arr, 4);
    cout << "ArraySeq RemoveAll" << endl;
    arrSeq->RemoveAll('a');
    cout << arrSeq->GetFirst() << arrSeq->Get(1) << arrSeq->GetLast() << endl;

    cout << "ArraySeq Concat" << endl;
    Sequence<char>* sss = arrSeq->Concat(subSeq);
    cout << sss->GetFirst() << sss->Get(3) << endl;*/

    /*LinkedList<char>* list1 = new LinkedList<char>(arr2, 4);
    cout << "LinkedList RemoveAt First" << endl;
    list1->RemoveAt(0);
    cout << "First: " << list1->GetFirst() << " Length: " << list1->GetLength() << endl;

    cout << "LinkedList RemoveAt Middle" << endl;
    list1->RemoveAt(1);
    cout << "First: " << list1->GetFirst() << " Last: " << list1->GetLast() << " Length: " << list1->GetLength() << endl;

    cout << "LinkedList RemoveAt Last" << endl;
    list1->RemoveAt(1);
    cout << "Last: " << list1->GetLast() << " Length: " << list1->GetLength() << endl;

    LinkedList<char>* list2 = new LinkedList<char>(arr2, 4);
    cout << "LinkedList Remove 'a'" << endl;
    list2->Remove('a');
    cout << "First: " << list2->GetFirst() << " Last: " << list2->GetLast() << " Length: " << list2->GetLength() << endl;

    cout << "LinkedList Remove 'd'" << endl;
    list2->Remove('d');
    cout << "First: " << list2->GetFirst() << " Last: " << list2->GetLast() << " Length: " << list2->GetLength() << endl;

    list2 = new LinkedList<char>(arr3, 5);
    cout << "LinkedList RemoveAll 'a'" << endl;
    list2->RemoveAll('a');
    cout << "First: " << list2->GetFirst() << " Last: " << list2->GetLast() << " Length: " << list2->GetLength() << endl;*/

    LinearForm<int>* linear1 = new LinearForm<int>(arri1, 4);
    (*linear1) *= 3;
    return 0;
}
