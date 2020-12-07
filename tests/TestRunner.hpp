#pragma once

#include "ArraySequenceTester/ArraySequenceTester.hpp"
#include "DynamicArrayTester/DynamicArrayTester.hpp"
#include "LinkedListTester/LinkedListTester.hpp"
#include "ListSequenceTester/ListSequenceTester.hpp"
#include "BinaryTreeTester/BinaryTreeTester.hpp"
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
    BinaryTreeTester();
    SetTester();
    PairTester();
    DictionaryTester();
    CacheTester();
}
