#pragma once 

#include "Resource.hpp"

namespace YAWN {
    class Image : public Resource {
    public:
        static Image* FromFile(const String& filename);

        virtual ~Image();

        const uint8* Data() const;

        int32 Width() const;

        int32 Height() const;

    protected:
        Image(uint8* data, int32 width, int32 height);

    private:
        uint8* _data = nullptr;
        const int32 _width = 0;
        const int32 _height = 0;
    };
}
