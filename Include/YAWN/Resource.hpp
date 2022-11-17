#pragma once 

#include "Managed.hpp"

namespace YAWN {
    class Resource : public Reference {
    public:
        virtual ~Resource() = default;
    };
}
