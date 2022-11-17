#pragma once 

#include "Memory.hpp"

#include <assert.h>

namespace YAWN {
    template<class T>
    class Optional {
    public:
        Optional() = default;

        Optional(const T& value)
            : _created(true) {
            new (_data) T(value);
        }

        Optional(const Optional<T>& optional)
            : _created(optional._created) {
            if (_created) {
                new (_data) T(optional.Value());
            }
        }

        ~Optional() {
            if (_created) {
                ((T*)_data)->~T();
            }
        }

        bool HasValue() const {
            return _created;
        }

        T& Value() {
            assert(_created);
            return *(T*)_data;
        }

        const T& Value() const {
            assert(_created);
            return *(T*)_data;
        }

    private:
        char _data[sizeof(T)];
        bool _created = false;
    };
}