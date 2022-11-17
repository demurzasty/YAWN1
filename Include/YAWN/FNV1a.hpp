#pragma once 

#include "Core.hpp"

namespace YAWN {
    template<class T>
    struct FNV1aTraits;

    template<>
    struct FNV1aTraits<uint32> {
        static constexpr uint32 InitNumber = 0x811c9dc5;
        static constexpr uint32 PrimeNumber = 16777619;
    };

    template<>
    struct FNV1aTraits<uint64> {
        static constexpr uint64 InitNumber = 0xcbf29ce484222325ULL;
        static constexpr uint64 PrimeNumber = 1099511628211ULL;
    };

    constexpr usize FNV1a(const char* str, usize count) noexcept {
        return ((count ? FNV1a(str, count - 1) : FNV1aTraits<usize>::InitNumber) ^ str[count]) * FNV1aTraits<usize>::PrimeNumber;
    }

    template<usize N>
    constexpr usize FNV1a(const char(&str)[N]) noexcept {
        return FNV1a(str, N - 1);
    }
}