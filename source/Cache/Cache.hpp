#pragma once

#include "../Sequence/Sequence.hpp"
#include "../ArraySequence/ArraySequence.hpp"
#include "../Dictionary/IDictionary.hpp"
#include "../Dictionary/DictionaryHash.hpp"
#include "../Dictionary/Pair.hpp"

using namespace std;

template <class K>
class Cache {
private:
    IDictionary<K, int>* dictionary;

    K _GetMaxKey();

public:
    Cache(int capacity);

    Cache(const Sequence<K>* sequence, int capacity);

    void Tick();

    void Update(const Sequence<K>* sequence);

    IDictionary<K, int>* Show();
};

template<class K>
Cache<K>::Cache(int capacity) {
    this->dictionary = new DictionaryHash<K, int>(capacity);
}

template<class K>
Cache<K>::Cache(const Sequence<K>* sequence, int capacity) {
    this->dictionary = new DictionaryHash<K, int>(capacity);

    Update(sequence);
}

template<class K>
void Cache<K>::Update(const Sequence<K>* sequence) {
    for (int i = 0; i < sequence->GetLength(); ++i) {
        K key = sequence->Get(i);

        if (this->dictionary->ContainsKey(key)) {
            this->dictionary->Change(key, 0);
        }
        else {
            if (this->dictionary->Count() >= this->dictionary->Capacity()) {
                K maxKey = this->_GetMaxKey();
                this->dictionary->Remove(maxKey);
            }

            this->dictionary->Add(key, 0);
        }

        this->Tick();
    }
}

template<class K>
void Cache<K>::Tick() {
    Sequence<K>* keysSequence = this->dictionary->GetKeys();

    for (int i = 0; i < keysSequence->GetLength(); ++i) {
        K key = keysSequence->Get(i);
        this->dictionary->Change(key, this->dictionary->Get(key) + 1);
    }
}

template<class K>
IDictionary<K, int>* Cache<K>::Show() {
    if (this->dictionary->Count() == 0) {
        return NULL;
    }

    return this->dictionary;
}

template<class K>
K Cache<K>::_GetMaxKey() {
    int max = -1;
    K maxKey = K();
    Sequence<K>* keysSequence = this->dictionary->GetKeys();

    for (int i = 0; i < keysSequence->GetLength(); ++i) {
        K currentKey = keysSequence->Get(i);
        int currentItem = this->dictionary->Get(keysSequence->Get(i));
        if (currentItem > max) {
            max = currentItem;
            maxKey = currentKey;
        }
    }

    return maxKey;
}

