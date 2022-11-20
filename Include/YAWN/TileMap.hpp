#pragma once 

#include "CanvasItem.hpp"
#include "Texture.hpp"
#include "Array.hpp"
#include "TileMapData.hpp"

namespace YAWN {
    class TileMap : public CanvasItem {
    public:
        TileMap();

        virtual ~TileMap();

        virtual void LateUpdate(float32 timeStep) override;

        void LoadTiles(Managed<TileMapData> data);

        void SetTile(int32 x, int32 y, int32 tileIndex);

        int32 GetTile(int32 x, int32 y);

        void SetTileSet(Managed<Texture> texture);

        const Managed<Texture>& TileSet() const;

    private:
        Id _id = None;
        Managed<Texture> _tileSet;
        int32 _width = 20;
        int32 _height = 12;
        int32 _cellWidth = 16;
        int32 _cellHeight = 16;
        Array<int32> _tiles;
        bool _dirty = true;
    };
}
