#pragma once 

#include "Array.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    template<class T>
    class ArrayView {
    public:
        ArrayView() = default;

        ArrayView(const ArrayView<T>&) = default;
        ArrayView& operator=(const ArrayView<T>&) = default;

        ArrayView(const T* data, usize size) : _data(data), _size(size) {}

        ArrayView(const Array<typename RemoveConst<T>::Type>& array) : _data(array.Data()), _size(array.Size()) {}

        T& operator[](usize index) {
            Assert(index < _size, "Index out of bound.");
            return _data[index];
        }

        const T& operator[](usize index) const {
            Assert(index < _size, "Index out of bound.");
            return _data[index];
        }

        T* Data() { return _data; }

        const T* Data() const { return _data; }

        usize Size() const { return _size; }

    public:
        T* begin() { return _data; }
        const T* begin() const { return _data; }

        T* end() { return _data + _size; }
        const T* end() const { return _data + size; }

    private:
        T* _data = nullptr;
        usize _size = 0;
    };
}