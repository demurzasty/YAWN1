#pragma once 

#include "Managed.hpp"
#include "String.hpp"

namespace YAWN {
    class Resource : public Reference {
    public:
        virtual ~Resource() = default;
    };
}
