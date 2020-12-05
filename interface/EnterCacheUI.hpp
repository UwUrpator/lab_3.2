#pragma once

#include <iostream>
#include <string>

#include "../source/Sequence/Sequence.hpp"
#include "../source/ArraySequence/ArraySequence.hpp"
#include "../source/Cache/Cache.hpp"
#include "basic/SelectorUI.hpp"
#include "basic/SingleField.hpp"
#include "basic/MultiField.hpp"

class EnterCacheUI {
private:
    int capacityOfCache;

    Cache<string>* cache;

    int cacheMenuChoice;
    int CacheMenuSelector();

    Sequence<string>* enterArrSeq(int size);

    void ShowCache();
    void UpdateCache();

public:
    EnterCacheUI();
};

EnterCacheUI::EnterCacheUI() {
    cout << endl;

    this->capacityOfCache = SingleField<int>("Enter the capacity of cache").item;
    this->cache = new Cache<string>(this->capacityOfCache);

    while(true) {
        this->cacheMenuChoice = this->CacheMenuSelector();

        switch (this->cacheMenuChoice) {
            case 1:
                this->ShowCache();
                break;
            case 2:
                this->UpdateCache();
                break;
            case 3:
                return;
        }
    }
}

int EnterCacheUI::CacheMenuSelector() {
    string answers[3] = {"Show cache", "Update cache", "Exit"};
    return SelectorUI("What do you want to do with cache", 3, answers).choice;
}

void EnterCacheUI::ShowCache() {
    IDictionary<string, int>* dictionary = this->cache->Show();

    if (!dictionary) {
        cout << "Cache is empty!" << endl;
        return;
    }

    Sequence<string>* keys = dictionary->GetKeys();

    for (int i = 0; i < keys->GetLength(); ++i) {
        string key = keys->Get(i);
        cout << key << ": " << dictionary->Get(key) << endl;
    }
}

void EnterCacheUI::UpdateCache() {
    int sizeOfSequence = SingleField<int>("Enter size of sequence").item;
    Sequence<string>* sequence = new ArraySequence<string>(sizeOfSequence);

    sequence = this->enterArrSeq(sizeOfSequence);

    this->cache->Update(sequence);
}

Sequence<string> *EnterCacheUI::enterArrSeq(int size) {
    string* arr = MultiField<string>("Enter values", size).items;

    Sequence<string>* seq = new ArraySequence<string>(arr, size);

    return seq;
}
