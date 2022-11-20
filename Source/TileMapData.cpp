#include <YAWN/TileMapData.hpp>

#include <stdio.h>

using namespace YAWN;

Managed<TileMapData> TileMapData::FromFile(const String& filename) {
    FILE* file = fopen(filename.CStr(), "r");
    if (!file) {
        return nullptr;
    }

    int32 width, height;
    Array<int32> tiles;

    if (fscanf(file, "%d", &width) == 0) {
        fclose(file);
        return nullptr;
    }

    if (fscanf(file, "%d", &height) == 0) {
        fclose(file);
        return nullptr;
    }

    tiles.Resize(width * height);
    for (usize i = 0; i < tiles.Size(); ++i) {
        if (fscanf(file, "%d", &tiles[i]) == 0) {
            fclose(file);
            return nullptr;
        }
    }

    fclose(file);
    return new TileMapData(width, height, tiles);
}

int32 TileMapData::Width() const {
    return _width;
}

int32 TileMapData::Height() const {
    return _height;
}

ArrayView<const int32> TileMapData::Tiles() const {
    return _tiles;
}

TileMapData::TileMapData(int32 width, int32 height, Array<int32> tiles)
    : _width(width), _height(height), _tiles(tiles) {
}