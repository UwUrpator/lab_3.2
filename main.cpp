#include <iostream>
#include "source/DynamicArray/DynamicArray.hpp"
#include "source/LinkedList/LinkedList.hpp"
#include "tests/DynamicArrayTester/DynamicArrayTester.hpp"
#include "tests/LinkedListTester/LinkedListTester.hpp"
#include "tests/ListSequenceTester/ListSequenceTester.hpp"
#include "tests/ArraySequenceTester/ArraySequenceTester.hpp"
#include "tests/LinearFormTester/LinearFormTester.hpp"

using namespace std;

int main() {
    DynamicArrayTester();
    LinkedListTester();
    ListSequenceTester();
    ArraySequenceTester();
    LinearFormTester();

    return 0;
}
