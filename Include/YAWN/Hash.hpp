#pragma once 

#include "String.hpp"

namespace YAWN {
    class Hash {
    public:
        usize operator()(uint8 value) const;

        usize operator()(uint16 value) const;

        usize operator()(uint32 value) const;

        usize operator()(uint64 value) const;

        usize operator()(int8 value) const;

        usize operator()(int16 value) const;

        usize operator()(int32 value) const;

        usize operator()(int64 value) const;

        usize operator()(Id value) const;

        usize operator()(const String& value) const;
    };
}
