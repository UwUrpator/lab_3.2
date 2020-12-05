#pragma once

#include "ArraySequenceTester/ArraySequenceTester.hpp"
#include "DynamicArrayTester/DynamicArrayTester.hpp"
#include "LinearFormTester/LinearFormTester.hpp"
#include "LinkedListTester/LinkedListTester.hpp"
#include "ListSequenceTester/ListSequenceTester.hpp"
#include "SorterTester/QuickSorterTester.hpp"
#include "SorterTester/ShellSorterTester.hpp"
#include "BinaryTreeTester/BinaryTreeTester.hpp"
#include "BinaryTreeTester/BinaryHeapTester.hpp"
#include "SetTester/SetTester.hpp"
#include "DictionaryTester/PairTester.hpp"
#include "DictionaryTester/DictionaryTester.hpp"
#include "CacheTester/CacheTester.hpp"

class TestRunner {
public:
    TestRunner();
};

TestRunner::TestRunner() {
    DynamicArrayTester();
    LinkedListTester();
    ListSequenceTester();
    ArraySequenceTester();
    QuickSorterTester();
    ShellSorterTester();
    BinaryTreeTester();
    BinaryHeapTester();
    SetTester();
    PairTester();
    DictionaryTester();
    //CacheTester();
}
