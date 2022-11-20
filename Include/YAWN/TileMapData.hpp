#pragma once 

#include "Resource.hpp"
#include "Array.hpp"
#include "ArrayView.hpp"

namespace YAWN {
    class TileMapData : public Resource {
    public:
        static Managed<TileMapData> FromFile(const String& filename);

        int32 Width() const;

        int32 Height() const;

        ArrayView<const int32> Tiles() const;

    private:
        TileMapData(int32 width, int32 height, Array<int32> tiles);

    private:
        int32 _width;
        int32 _height;
        Array<int32> _tiles;
    };
}