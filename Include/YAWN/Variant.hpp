#pragma once 

#include "Array.hpp"
#include "Map.hpp"
#include "Vector2.hpp"
#include "String.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    enum class VariantType {
        Null,
        Bool,
        Integer, // int64 internally
        Float,   // float64 internally
        Vector2,
        String,
        Array, // Array<Variant> internally
        Map, // Map<String, Variant> internally
    };

    class Variant {
    public:
        Variant();

    private:
        VariantType _type = VariantType::Null;
        char _data[MaxTypesSize<bool, int64, float64, Vector2, String, Array<Variant>, Map<String, Variant>>::Value];
    };
}
