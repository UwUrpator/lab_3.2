#pragma once

#include <iostream>
#include "string"

#include "../source/Dictionary/DictionarySequence.hpp"
#include "../source/Dictionary/DictionaryBinaryTree.hpp"
#include "../source/Dictionary/DictionaryHash.hpp"
#include "../tests/DictionaryTester/IDictionaryTester.hpp"
#include "../Informator/Informator.hpp"

class DictionaryTester {
public:
    DictionaryTester();
};

DictionaryTester::DictionaryTester() {
    //IDictionaryTester<DictionarySequence<string, int>>("DictionarySequence");
    //IDictionaryTester<DictionaryBinaryTree<string, int>>("DictionaryBinaryTree");
    IDictionaryTester<DictionaryHash<string, int>>("DictionaryHash");
}
