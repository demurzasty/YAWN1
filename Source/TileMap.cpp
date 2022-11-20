#include <YAWN/TileMap.hpp>
#include <YAWN/GraphicsDevice.hpp>

using namespace YAWN;

TileMap::TileMap() {
    _id = GraphicsDevice::CreateCanvasItem();
}

TileMap::~TileMap() {
    GraphicsDevice::DestroyCanvasItem(_id);
}

void TileMap::LateUpdate(float32 timeStep) {
    CanvasItem::LateUpdate(timeStep);

    if (_dirty && _tileSet) {
        Array<Vector2> positions(_tiles.Size() * 6);
        Array<Vector2> texcoords(_tiles.Size() * 6);

        int32 tileSetWidth = _tileSet->Width();
        int32 tileSetHeight = _tileSet->Height();

        int32 tileSetWidthInTiles = _tileSet->Width() / _cellWidth;
        int32 tileSetHeightInTiles = _tileSet->Height() / _cellHeight;

        int32 tileCount = 0;
        for (usize i = 0; i < _tiles.Size(); ++i) {
            if (_tiles[i] > -1) {
                float32 x = float32(i % _width) * _cellWidth;
                float32 y = float32(i / _width) * _cellHeight;

                positions[tileCount * 6 + 0] = Vector2(x, y);
                positions[tileCount * 6 + 1] = Vector2(x, y + _cellHeight);
                positions[tileCount * 6 + 2] = Vector2(x + _cellWidth, y + _cellHeight);

                positions[tileCount * 6 + 3] = Vector2(x + _cellWidth, y + _cellHeight);
                positions[tileCount * 6 + 4] = Vector2(x + _cellWidth, y);
                positions[tileCount * 6 + 5] = Vector2(x, y);

                float32 tw = float32(_cellWidth) / tileSetWidth;
                float32 th = float32(_cellHeight) / tileSetHeight;
                float32 tx = float32(_tiles[i] % tileSetWidthInTiles) * tw;
                float32 ty = float32(_tiles[i] / tileSetWidthInTiles) * th;

                texcoords[tileCount * 6 + 0] = Vector2(tx, ty);
                texcoords[tileCount * 6 + 1] = Vector2(tx, ty + th);
                texcoords[tileCount * 6 + 2] = Vector2(tx + tw, ty + th);

                texcoords[tileCount * 6 + 3] = Vector2(tx + tw, ty + th);
                texcoords[tileCount * 6 + 4] = Vector2(tx + tw, ty);
                texcoords[tileCount * 6 + 5] = Vector2(tx, ty);

                tileCount++;
            }
        }

        GraphicsDevice::SetCanvasItemTexture(_id, TileSet()->Id());
        GraphicsDevice::SetCanvasItemPrimitives(_id, positions.Data(), nullptr, texcoords.Data(), tileCount * 6);

        _dirty = false;
    }
}

void TileMap::LoadTiles(Managed<TileMapData> data) {
    _width = data->Width();
    _height = data->Height();
    _tiles = Array<int32>(data->Tiles().Data(), data->Tiles().Size());
    _dirty = true;
}

void TileMap::SetTile(int32 x, int32 y, int32 tileIndex) {
    int32 index = y * _width + x;
    if (index >= _tiles.Size()) {
        _tiles.Resize(_width * _height, -1);
    }

    _dirty = tileIndex != _tiles[index];
    _tiles[index] = tileIndex;
}

int32 TileMap::GetTile(int32 x, int32 y) {
    int32 index = y * _width + x;
    if (index >= _tiles.Size()) {
        return -1;
    }

    return _tiles[index];
}

void TileMap::SetTileSet(Managed<Texture> texture) {
    _dirty = texture != _tileSet;
    _tileSet = texture;
}

const Managed<Texture>& TileMap::TileSet() const {
    return _tileSet;
}
