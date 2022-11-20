#pragma once 

#include "GraphicsResource.hpp"
#include "Image.hpp"

namespace YAWN {
    class Texture : public GraphicsResource {
    public:
        static Managed<Texture> FromFile(const String& filename);

        static Managed<Texture> FromImage(Image* image);

        Texture();

        virtual ~Texture();

        void SetData(const uint8* data, int32 width, int32 height);

        int32 Width() const;

        int32 Height() const;

    private:
        int32 _width = 0;
        int32 _height = 0;
    };
}