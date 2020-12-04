#pragma once

#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/Sequence/Sequence.hpp"
#include "../source/Dictionary/IDictionary.hpp"
#include "../source/Dictionary/DictionaryBinaryTree.hpp"
#include "../source/Cache/Cache.hpp"

using namespace std;

class CacheTester {
private:
    string *dummyStringArr;
    int dummyStringArrLen;

    Sequence<string>* sequence;
    int capacity;

public:
    CacheTester();

    void TestCache();
};

CacheTester::CacheTester() {
    this->dummyStringArr = new string[6];
    this->dummyStringArr[0] = "Peter";
    this->dummyStringArr[1] = "Bob";
    this->dummyStringArr[2] = "Clara";
    this->dummyStringArr[3] = "Clara";
    this->dummyStringArr[4] = "Peter";
    this->dummyStringArr[5] = "Bill";
    this->dummyStringArrLen = 6;

    this->sequence = new ArraySequence<string>(this->dummyStringArr, this->dummyStringArrLen);
    this->capacity = 3;

    this->TestCache();
}

void CacheTester::TestCache() {
    Cache<string>* cache = new Cache<string>(this->sequence, this->capacity);
    cout << "endl";
}

