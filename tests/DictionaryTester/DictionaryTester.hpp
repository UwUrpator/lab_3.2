#pragma once

#include <iostream>
#include "string"

#include "../source/Dictionary/DictionarySequence.hpp"
#include "../tests/DictionaryTester/IDictionaryTester.hpp"
#include "../Informator/Informator.hpp"

class DictionaryTester {
public:
    DictionaryTester();
};

DictionaryTester::DictionaryTester() {
    IDictionaryTester<DictionarySequence<string, int>>("DictionarySequence");
    //IDictionaryTester<SetBinaryTree<int>>("SetBinaryTree");
}
