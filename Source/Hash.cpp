#include <YAWN/Hash.hpp>

using namespace YAWN;

usize Hash::operator()(uint8 value) const {
    return usize(value);
}

usize Hash::operator()(uint16 value) const {
    return usize(value);
}

usize Hash::operator()(uint32 value) const {
    return usize(value);
}

usize Hash::operator()(uint64 value) const {
    return usize(value);
}

usize Hash::operator()(int8 value) const {
    return usize(value);
}

usize Hash::operator()(int16 value) const {
    return usize(value);
}

usize Hash::operator()(int32 value) const {
    return usize(value);
}

usize Hash::operator()(int64 value) const {
    return usize(value);
}

usize Hash::operator()(Id value) const {
    return usize(value);
}

usize Hash::operator()(const String& value) const {
    return value.Hash();
}
