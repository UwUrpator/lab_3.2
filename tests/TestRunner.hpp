#pragma once

#include "ArraySequenceTester/ArraySequenceTester.hpp"
#include "DynamicArrayTester/DynamicArrayTester.hpp"
#include "LinearFormTester/LinearFormTester.hpp"
#include "LinkedListTester/LinkedListTester.hpp"
#include "ListSequenceTester/ListSequenceTester.hpp"
#include "SorterTester/QuickSorterTester.hpp"

class TestRunner {
public:
    TestRunner();
};

TestRunner::TestRunner() {
    DynamicArrayTester();
    LinkedListTester();
    ListSequenceTester();
    ArraySequenceTester();
    //LinearFormTester();
    QuickSorterTester();
}
