#include <YAWN/Variant.hpp>

#include <string.h>

using namespace YAWN;

Variant::Variant(decltype(nullptr))
    : _type(VariantType::Null) {
}

Variant::Variant(bool value)
    : _type(VariantType::Bool) {
    new (_data) bool(value);
}

Variant::Variant(int32 value)
    : _type(VariantType::Int) {
    new (_data) int64(value);
}

Variant::Variant(int64 value)
    : _type(VariantType::Int) {
    new (_data) int64(value);
}

Variant::Variant(float32 value)
    : _type(VariantType::Float) {
    new (_data) float64(value);
}

Variant::Variant(float64 value)
    : _type(VariantType::Float) {
    new (_data) float64(value);
}

Variant::Variant(const YAWN::Color& value)
    : _type(VariantType::Color) {
    new (_data) YAWN::Color(value);
}

Variant::Variant(const YAWN::Vector2& value)
    : _type(VariantType::Vector2) {
    new (_data) YAWN::Vector2(value);
}

Variant::Variant(const YAWN::String& value)
    : _type(VariantType::String) {
    new (_data) YAWN::String(value);
}

Variant::Variant(const YAWN::Array<Variant>& value)
    : _type(VariantType::Array) {
    new (_data) YAWN::Array<Variant>(value);
}

Variant::Variant(const YAWN::Map<YAWN::String, Variant>& value)
    : _type(VariantType::Map) {
    new (_data) YAWN::Map<YAWN::String, Variant>(value);
}

Variant::Variant(const Variant& variant) {
    *this = variant;
}

Variant::Variant(Variant&& variant) noexcept
    : _type(variant._type) {
    memcpy(_data, variant._data, sizeof(_data));
    variant._type = VariantType::Null;
}

Variant::~Variant() {
    Reset();
}

Variant& Variant::operator=(const Variant& variant) {
    Reset();

    switch (variant._type) {
    case VariantType::Bool:
        new (_data) bool(variant.Bool());
        break;
    case VariantType::Int:
        new (_data) int64(variant.Int());
        break;
    case VariantType::Float:
        new (_data) float64(variant.Float());
        break;
    case VariantType::String:
        new (_data) YAWN::String(variant.String());
        break;
    case VariantType::Color:
        new (_data) YAWN::Color(variant.Color());
        break;
    case VariantType::Vector2:
        new (_data) YAWN::Vector2(variant.Vector2());
        break;
    case VariantType::Array:
        new (_data) YAWN::Array<Variant>(variant.Array());
        break;
    case VariantType::Map:
        new (_data) YAWN::Map<YAWN::String, Variant>(variant.Map());
        break;
    }

    _type = variant._type;
    return *this;
}

Variant& Variant::operator=(Variant&& variant) noexcept {
    Reset();
    _type = variant._type;
    memcpy(_data, variant._data, sizeof(_data));
    variant._type = VariantType::Null;
    return *this;
}

void Variant::Reset() {
    switch (_type) {
    case VariantType::String:
        reinterpret_cast<YAWN::String*>(_data)->~String();
        break;
    case VariantType::Array:
        reinterpret_cast<YAWN::Array<Variant>*>(_data)->~Array();
        break;
    case VariantType::Map:
        reinterpret_cast<YAWN::Map<YAWN::String, Variant>*>(_data)->~Map();
        break;
    }

    _type = VariantType::Null;
}

bool Variant::Bool() const {
    if (_type == VariantType::Null) {
        return false;
    }

    Assert(_type == VariantType::Bool, "Invalid cast.");
    return *reinterpret_cast<const bool*>(_data);
}

int64 Variant::Int() const {
    if (_type == VariantType::Float) {
        return int64(Float());
    }

    Assert(_type == VariantType::Int, "Invalid cast.");
    return *reinterpret_cast<const int64*>(_data);
}

float64 Variant::Float() const {
    if (_type == VariantType::Int) {
        return float64(Int());
    }

    Assert(_type == VariantType::Float, "Invalid cast.");
    return *reinterpret_cast<const float64*>(_data);
}

const String& Variant::String() const {
    Assert(_type == VariantType::String, "Invalid cast.");
    return *reinterpret_cast<const YAWN::String*>(_data);
}

const Color& Variant::Color() const {
    Assert(_type == VariantType::Color, "Invalid cast.");
    return *reinterpret_cast<const YAWN::Color*>(_data);
}

const Vector2& Variant::Vector2() const {
    Assert(_type == VariantType::Vector2, "Invalid cast.");
    return *reinterpret_cast<const YAWN::Vector2*>(_data);
}

const Array<Variant>& Variant::Array() const {
    Assert(_type == VariantType::Array, "Invalid cast.");
    return *reinterpret_cast<const YAWN::Array<Variant>*>(_data);
}

const Map<String, Variant>& Variant::Map() const {
    Assert(_type == VariantType::Map, "Invalid cast.");
    return *reinterpret_cast<const YAWN::Map<YAWN::String, Variant>*>(_data);
}

Variant::operator bool() const {
    return Bool();
}

Variant::operator int32() const {
    return int32(Int());
}

Variant::operator int64() const {
    return Int();
}

Variant::operator float32() const {
    return float32(Float());
}

Variant::operator float64() const {
    return Float();
}

Variant::operator YAWN::Color() const {
    return Color();
}

Variant::operator YAWN::Vector2() const {
    return Vector2();
}

const Variant& Variant::operator[](usize index) const {
    return Array()[index];
}

const Variant& Variant::operator[](const YAWN::String& key) const {
    return Map()[key];
}

VariantType Variant::Type() const {
    return _type;
}
