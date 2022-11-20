#pragma once 

#include "Array.hpp"

namespace YAWN {
    template<class TKey, class TValue>
    class Map {
    public:
        struct KeyValue {
            KeyValue() = default;

            KeyValue(const TKey& key, const TValue& value) : Key(key), Value(value) {}

            KeyValue(const TKey& key, TValue&& value) : Key(key), Value((TValue&&)(value)) {}

            KeyValue(const KeyValue&) = default;
            KeyValue& operator=(const KeyValue&) = default;

            KeyValue(KeyValue&&) = default;
            KeyValue& operator=(KeyValue&&) = default;

            TKey Key = TKey();
            TValue Value = TValue();
        };

    public:
        Map() = default;

        Map(const Map<TKey, TValue>&) = default;
        Map<TKey, TValue>& operator=(const Map<TKey, TValue>&) = default;

        void Insert(const TKey& key, const TValue& value) {
            usize index = BinarySearch(key);
            CheckReturn(index == _array.Size() || _array[index].Key != key, "An element with the same key already exists.");
            _array.Insert(index, KeyValue(key, value));
        }

        bool Remove(const TKey& key) {
            usize index = BinarySearch(key);
            if (index < _array.Size() && _array[index].Key == key) {
                _array.Remove(index);
                return true;
            }

            return false;
        }

        void Clear() {
            _array.Clear();
        }

        bool Contains(const TKey& key) const {
            usize index = BinarySearch(key);
            return index < _array.Size() && _array[index].Key == key;
        }

        TValue& operator[](const TKey& key) {
            usize index = BinarySearch(key);
            if (index == _array.Size() || _array[index].Key != key) {
                _array.Insert(index, KeyValue(key, TValue()));
            }

            return _array[index].Value;
        }

        const TValue& operator[](const TKey& key) const {
            usize index = BinarySearch(key);
            Assert(index < _array.Size() && _array[index].Key == key, "An element does not exist.");
            return _array[index].Value;
        }

        usize Size() const {
            return _array.Size();
        }

        usize Capacity() const {
            return _array.Capacity();
        }

    public:
        KeyValue* begin() { return _array.begin(); }
        const KeyValue* begin() const { return _array.begin(); }

        KeyValue* end() { return _array.end(); }
        const KeyValue* end() const { return _array.end(); }

    private:
        usize BinarySearch(const TKey& key) const {
            usize low = 0, high = _array.Size();

            while (low < high) {
                const usize middle = low + (high - low) / 2;

                if (_array[middle].Key < key) {
                    low = middle + 1;
                } else {
                    high = middle;
                }
            }

            return high;
        }

    private:
        Array<KeyValue> _array;
    };
}