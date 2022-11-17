#pragma once 

#include "Resource.hpp"

namespace YAWN {
    class GraphicsResource : public Resource {
    public:
        GraphicsResource(YAWN::Id id);

        virtual ~GraphicsResource() = default;

        YAWN::Id Id() const;

    private:
        YAWN::Id _id = None;
    };
}