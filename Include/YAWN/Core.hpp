#pragma once 

namespace YAWN {
    /* Primitive Types */

    using int8 = signed char;
    using int16 = signed short;
    using int32 = signed int;
    using int64 = signed long long;

    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long long;

    using float32 = float;
    using float64 = double;

    using usize = decltype(sizeof(void*));
    using isize = decltype((int32*)(0) - (int32*)(0));

    /* Basic Types */

    enum class Id : usize;

    /* Constants */

    constexpr Id None = Id(~0);

    /* Complex Types */

    class NonCopyable {
    public:
        NonCopyable() = default;

        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    class NonInstantiable {
    public:
        NonInstantiable() = delete;

        NonInstantiable(const NonInstantiable&) = delete;
        NonInstantiable& operator=(const NonInstantiable&) = delete;
    };
}
