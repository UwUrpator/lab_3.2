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
    IDictionary<K, int>* cache;

public:
    Cache(Sequence<K>, int capacity);

    void Update(Sequence<K>);
    IDictionary<K, int> Show();
};

template<class K>
Cache<K>::Cache(Sequence<K> sequence, int capacity) {
    this->cache = new DictionaryBinaryTree<K, int>(capacity);

    for (int i = 0; i < sequence.GetLength(); ++i) {
        K key = sequence.Get(i);
        if (this->cache->ContainsKey(key)) {
            this->cache->Change(key, this->cache->Get(key) + 1);
        }
        else {
            if (this->cache->Count() < this->cache->Capacity()) {
                this->cache->Add(key, 1);
            }
        }
    }
}
