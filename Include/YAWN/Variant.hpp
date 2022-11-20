#pragma once 

#include "Array.hpp"
#include "Map.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "String.hpp"
#include "TypeTraits.hpp"

namespace YAWN {
    enum class VariantType {
        Null,
        Bool,
        Int, // int64 internally
        Float,   // float64 internally
        Color,
        Vector2,
        String,
        Array, // Array<Variant> internally
        Map, // Map<String, Variant> internally
    };

    class Variant {
    public:
        Variant() = default;

        Variant(decltype(nullptr));

        Variant(bool value);

        Variant(int32 value);

        Variant(int64 value);

        Variant(float32 value);

        Variant(float64 value);

        Variant(const Color& value);

        Variant(const Vector2& value);

        Variant(const String& value);

        Variant(const Array<Variant>& value);

        Variant(const Map<String, Variant>& value);

        Variant(const Variant& variant);

        Variant(Variant&& variant) noexcept;

        ~Variant();

        Variant& operator=(const Variant& variant);

        Variant& operator=(Variant&& variant) noexcept;

        void Reset();

        bool Bool() const;

        int64 Int() const;

        float64 Float() const;

        const String& String() const;

        const Color& Color() const;

        const Vector2& Vector2() const;

        const Array<Variant>& Array() const;

        const Map<YAWN::String, Variant>& Map() const;

        operator bool() const;

        operator int32() const;

        operator int64() const;

        operator float32() const;

        operator float64() const;

        operator YAWN::Color() const;

        operator YAWN::Vector2() const;

        const Variant& operator[](usize index) const;

        const Variant& operator[](const YAWN::String& key) const;

        VariantType Type() const;

    private:
        VariantType _type = VariantType::Null;
        uint8 _data[MaxTypesSize<bool, int64, float64, YAWN::Color, YAWN::Vector2, YAWN::String, YAWN::Array<Variant>, YAWN::Map<YAWN::String, Variant>>::Value]{};
    };
}
