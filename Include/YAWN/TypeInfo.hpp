#pragma once 

#include "FNV1a.hpp"

#if defined __clang__ || defined __GNUC__
#   define YAWN_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#   define YAWN_PRETTY_FUNCTION __FUNCSIG__
#endif

namespace YAWN {
    template<class T>
    constexpr Id TypeId() noexcept {
        return Id(FNV1a(YAWN_PRETTY_FUNCTION));
    }
}
