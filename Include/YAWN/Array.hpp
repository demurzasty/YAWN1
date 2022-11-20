#pragma once 

#include "Core.hpp"
#include "Memory.hpp"
#include "Error.hpp"
#include "Optional.hpp"

namespace YAWN {
    template<class T>
    class Array {
    public:
        Array() = default;

        explicit Array(usize size)
            : _capacity(size), _size(size) {
            _data = Memory::Allocate<T>(_capacity);
            for (usize i = 0; i < _size; ++i) {
                new (_data + i) T();
            }
        }

        Array(const T* data, usize size) {
            CheckReturn(size == 0 || data, "No input data.");

            _data = Memory::Allocate<T>(size);
            _capacity = size;
            _size = size;

            for (usize i = 0; i < _size; ++i) {
                new (_data + i) T(data[i]);
            }
        }

        Array(const Array<T>& array)
            : _capacity(array._size), _size(array._size) {
            _data = Memory::Allocate<T>(_size);

            for (usize i = 0; i < _size; ++i) {
                new (_data + i) T(array[i]);
            }
        }

        Array(Array<T>&& array)
            : _data(array._data), _capacity(array._capacity), _size(array._size) {
            array._data = nullptr;
            array._capacity = 0;
            array._size = 0;
        }

        Array<T>& operator=(const Array<T>& array) noexcept {
            for (usize i = 0; i < _size; ++i) {
                (_data + i)->~T();
            }

            _size = array._size;

            if (_capacity < _size) {
                _data = Memory::Reallocate<T>(_data, _size);
                _capacity = _size;
            }

            for (usize i = 0; i < _size; ++i) {
                new (_data + i) T(array[i]);
            }

            return *this;
        }

        Array<T>& operator=(Array<T>&& array) noexcept {
            for (usize i = 0; i < _size; ++i) {
                (_data + i)->~T();
            }

            Memory::Deallocate(_data);

            _data = array._data;
            _capacity = array._capacity;
            _size = array._size;

            array._data = nullptr;
            array._capacity = 0;
            array._size = 0;
            return *this;
        }

        ~Array() {
            for (usize i = 0; i < _size; ++i) {
                (_data + i)->~T();
            }

            Memory::Deallocate(_data);
        }

        template<class Func>
        void Sort(Func comparator) {
            if (_size == 0) {
                return;
            }

            for (usize i = 0; i < _size - 1; i++) {
                for (usize j = 0; j < _size - i - 1; j++) {
                    if (comparator(_data[j], _data[j + 1])) {
                        T temp = _data[j];
                        _data[j] = _data[j + 1];
                        _data[j + 1] = temp;
                    }
                }
            }
        }

        void Sort() {
            Sort([](const T& a, const T& b) -> bool {
                return a < b;
            });
        }

        void PushBack(const T& value) {
            Preserve();

            new (_data + _size) T(value);

            _size++;
        }

        void PushFront(const T& value) {
            Insert(0, value);
        }

        void PopBack() {
            CheckReturn(_size > 0, "Collection is empty.");

            _size--;

            (_data + _size)->~T();
        }

        void PopFront() {
            Remove(0);
        }

        void Insert(usize index, const T& value) {
            CheckReturn(index <= _size, "Index out of bound.");

            Preserve();

            for (usize i = _size; i > index; --i) {
                new (_data + i) T((T&&)_data[i - 1]);
                (_data + i - 1)->~T();
            }

            new (_data + index) T((T&&)value);

            _size++;
        }

        void Remove(usize index) {
            CheckReturn(index < _size, "Index out of bound.");

            for (usize i = index; i < _size - 1; ++i) {
                (_data + i)->~T();
                new (_data + i) T(_data[i + 1]);
            }

            _size--;

            (_data + _size)->~T();
        }

        void Clear() {
            for (usize i = 0; i < _size; ++i) {
                (_data + i)->~T();
            }

            _size = 0;
        }

        void Resize(usize size, T defaultValue = T()) {
            if (size > _capacity) {
                Reserve(size);
            }

            for (usize i = _size; i > size; --i) {
                (_data + i)->~T();
            }

            for (usize i = _size; i < size; ++i) {
                new (_data + i) T(defaultValue);
            }

            _size = size;
        }

        void Reserve(usize capacity) {
            if (capacity > _capacity) {
                _data = Memory::Reallocate<T>(_data, capacity);
                _capacity = capacity;
            }
        }

        Optional<usize> Find(const T& value) const {
            for (usize i = 0; i < _size; ++i) {
                if (_data[i] == value) {
                    return Optional<usize>(i);
                }
            }

            return Optional<usize>();
        }

        bool Contains(const T& value) {
            for (usize i = 0; i < _size; ++i) {
                if (_data[i] == value) {
                    return true;
                }
            }

            return false;
        }

        T& operator[](usize index) {
            Assert(index < _size, "Index out of bound.");
            return _data[index];
        }

        const T& operator[](usize index) const {
            Assert(index < _size, "Index out of bound.");
            return _data[index];
        }

        T& Back() {
            Assert(_size > 0, "Collection is empty.");
            return _data[_size - 1];
        }

        const T& Back() const {
            Assert(_size > 0, "Collection is empty.");
            return _data[_size - 1];
        }

        T& Front() {
            Assert(_size > 0, "Collection is empty.");
            return _data[0];
        }

        const T& Front() const {
            Assert(_size > 0, "Collection is empty.");
            return _data[0];
        }

        T* Data() { return _data; }

        const T* Data() const { return _data; }

        usize Size() const { return _size; }

        usize Capacity() const { return _capacity; }

    public:
        T* begin() { return _data; }
        const T* begin() const { return _data; }

        T* end() { return _data + _size; }
        const T* end() const { return _data + _size; }

    private:
        inline void Preserve() {
            if (_size == _capacity) {
                Reserve(_capacity == 0 ? 1 : (_capacity << 1));
            }
        }

    private:
        T* _data = nullptr;
        usize _capacity = 0;
        usize _size = 0;
    };
}
