#include <iostream>
#include "source/DynamicArray/DynamicArray.hpp"
#include "source/LinkedList/LinkedList.hpp"
#include "tests/DynamicArrayTester/DynamicArrayTester.hpp"
#include "tests/LinkedListTester/LinkedListTester.hpp"

using namespace std;

int main() {
    DynamicArrayTester();
    LinkedListTester();
    /*char arr1[3] = {'a', 'b', 'c'};
    char arr2[4] = {'a', 'b', 'c', 'd'};
    char arr3[5] = {'a', 'a', 'b', 'a', 'a'};
    int arri1[4] = {1, 2, 3, 4};

   LinkedList<char>* llist1 = new LinkedList<char>(arr1, 3);
   LinkedList<char>* llist2 = new LinkedList<char>(*llist1);

   cout << llist2->GetLast();*/

    return 0;
}
