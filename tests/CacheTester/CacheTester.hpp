#pragma once

#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/Sequence/Sequence.hpp"
#include "../source/Dictionary/IDictionary.hpp"
#include "../source/Dictionary/DictionaryBinaryTree.hpp"
#include "../source/Cache/Cache.hpp"

using namespace std;

class CacheTester {
private:
    string *dummyStringArr1;
    string *dummyStringArr2;
    int dummyStringArrLen1;
    int dummyStringArrLen2;

    Sequence<string>* sequence1;
    Sequence<string>* sequence2;
    int capacity;

public:
    CacheTester();

    void TestShow();
    void TestUpdate();
};

CacheTester::CacheTester() {
    this->dummyStringArr1 = new string[6];
    this->dummyStringArr1[0] = "Peter";
    this->dummyStringArr1[1] = "Bob";
    this->dummyStringArr1[2] = "Clara";
    this->dummyStringArr1[3] = "Clara";
    this->dummyStringArr1[4] = "Peter";
    this->dummyStringArr1[5] = "Bill";
    this->dummyStringArrLen1 = 6;

    this->dummyStringArr2 = new string[6];
    this->dummyStringArr2[0] = "Bob";
    this->dummyStringArr2[1] = "Bob";
    this->dummyStringArr2[2] = "Peter";
    this->dummyStringArr2[3] = "Bill";
    this->dummyStringArr2[4] = "Clara";
    this->dummyStringArr2[5] = "Bill";
    this->dummyStringArrLen2 = 6;

    this->sequence1 = new ArraySequence<string>(this->dummyStringArr1, this->dummyStringArrLen1);
    this->sequence2 = new ArraySequence<string>(this->dummyStringArr2, this->dummyStringArrLen2);
    this->capacity = 3;

    this->TestShow();
    this->TestUpdate();
}

void CacheTester::TestShow() {
    Cache<string>* cache = new Cache<string>(this->sequence1, this->capacity);

    IDictionary<string, int>* dictionary = cache->Show();

    Informator(
        (
            dictionary->Get("Bill") == 1 &&
            dictionary->Get("Peter") == 2 &&
            dictionary->Get("Clara") == 3
        ),
        "Success: IDictionary<K, T>* Cache::Show(); Correct cache is shown",
        "Error: IDictionary<K, T>* Cache::Show(); Incorrect cache is shown"
    );
}

void CacheTester::TestUpdate() {
    Cache<string>* cache = new Cache<string>(this->sequence1, this->capacity);
    cache->Update(this->sequence2);

    IDictionary<string, int>* dictionary = cache->Show();

    Informator(
            (
                    dictionary->Get("Bill") == 1 &&
                    dictionary->Get("Clara") == 2 &&
                    dictionary->Get("Peter") == 4
            ),
            "Success: IDictionary<K, T>* Cache::Update(); Correct cache after update",
            "Error: IDictionary<K, T>* Cache::Update(); Incorrect cache after update"
    );
}
