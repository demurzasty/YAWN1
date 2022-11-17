#pragma once 

namespace YAWN {
    template<class T>
    struct RemoveReference {
        using Type = T;
    };

    template<class T>
    struct RemoveReference<T&> {
        using Type = T;
    };

    template<class T>
    struct RemoveReference<T&&> {
        using Type = T;
    };
    
    template<class T>
    struct RemoveConst {
        using Type = T;
    };

    template<class T>
    struct RemoveConst<const T> {
        using Type = T;
    };

    template<class T>
    struct RemoveReferenceConst {
        using Type = typename RemoveConst<typename RemoveReference<T>::Type>::Type;
    };

    template<usize Arg0, usize... Args>
    struct StaticMax;

    template<usize Arg>
    struct StaticMax<Arg> {
        static constexpr usize Value = Arg;
    };

    template<usize Arg0, usize Arg1, usize ... Args>
    struct StaticMax<Arg0, Arg1, Args...> {
        static constexpr usize Value = Arg0 >= Arg1 ? StaticMax<Arg0, Args...>::Value : StaticMax<Arg1, Args...>::Value;
    };

    template<typename... Types>
    struct MaxTypesSize {
        static constexpr usize Value = StaticMax<sizeof(Types)...>::Value;
    };
}
