#pragma once 

#include "Core.hpp"

inline void* operator new([[maybe_unused]] size_t size, void* ptr) noexcept {
    return ptr;
}

namespace YAWN {
    class Memory : public NonInstantiable {
    public:
        static void* Allocate(size_t size, size_t count);

        static void* Reallocate(void* data, size_t size, size_t count);

        static void Deallocate(void* data);

        template<class T>
        static T* Allocate(size_t count) {
            return (T*)Allocate(sizeof(T), count);
        }

        template<class T>
        static T* Reallocate(T* data, size_t count) {
            return (T*)Reallocate(data, sizeof(T), count);
        }
    };
}
