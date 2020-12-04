#pragma once

#include "../Sequence/Sequence.hpp"
#include "../ArraySequence/ArraySequence.hpp"
#include "../Dictionary/IDictionary.hpp"
#include "../Dictionary/DictionaryBinaryTree.hpp"
#include "../Dictionary/Pair.hpp"

using namespace std;

template <class K>
class Cache {
private:
    IDictionary<K, int>* dictionary;

public:
    Cache(const Sequence<K>* sequence, int capacity);

    void Tick();

    void Update(const Sequence<K>* sequence);

    //IDictionary<K, int> Show();
};

template<class K>
Cache<K>::Cache(const Sequence<K>* sequence, int capacity) {
    this->dictionary = new DictionaryBinaryTree<K, int>(capacity);

    Update(sequence);

    /*for (int i = 0; i < sequence.GetLength(); ++i) {
        K key = sequence.Get(i);
        if (this->dictionary->ContainsKey(key)) {
            this->dictionary->Change(key, this->dictionary->Get(key) + 1);
        }
        else {
            if (this->dictionary->Count() < this->dictionary->Capacity()) {
                this->dictionary->Add(key, 1);
            }
        }
    }*/
}

template<class K>
void Cache<K>::Update(const Sequence<K>* sequence) {
    for (int i = 0; i < sequence->GetLength(); ++i) {
        K key = sequence->Get(i);

        if (this->dictionary->ContainsKey(key)) {
            this->dictionary->Change(key, 0);
        }
        else {
            if (this->dictionary->Count() < this->dictionary->Capacity()) {
                this->dictionary->Add(key, 0);
            }
            else {
                /*K oldKey = this->dictionary->GetKeyByIndex(0);
                this->dictionary->Change(oldKey, 0);*/
            }
        }

        this->Tick();
    }
}

template<class K>
void Cache<K>::Tick() {
    for (int i = 0; i < this->dictionary->Count(); ++i) {
        /*K key = this->dictionary->GetKeyByIndex(i);
        this->dictionary->Change(key, this->dictionary->Get(key) + 1);*/
    }
}

