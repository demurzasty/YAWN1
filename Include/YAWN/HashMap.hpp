#pragma once 

#include "Map.hpp"
#include "Hash.hpp"

namespace YAWN {
    template<class TKey, class TValue, class THash = Hash, usize TableSize = 1024>
    class HashMap : public NonCopyable {
    public:
        using Bucket = Map<TKey, TValue>;

    public:
        HashMap() {
            _buckets = new Bucket[TableSize];
        }

        ~HashMap() {
            delete[] _buckets;
        }

        void Insert(const TKey& key, const TValue& value) {
            usize index = _hash(key) % TableSize;
            _buckets[index].Insert(key, value);
        }

        bool Remove(const TKey& key) {
            usize index = _hash(key) % TableSize;
            return _buckets[index].Remove(key);
        }

        bool Contains(const TKey& key) const {
            usize index = _hash(key) % TableSize;
            return _buckets[index].Contains(key);
        }

        TValue& operator[](const TKey& key) {
            usize index = _hash(key) % TableSize;
            return _buckets[index][key];
        }

        const TValue& operator[](const TKey& key) const {
            usize index = _hash(key) % TableSize;
            return _buckets[index][key];
        }

    private:
        THash _hash;
        Bucket* _buckets;
    };
}
