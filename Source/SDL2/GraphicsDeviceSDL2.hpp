#pragma once 

#include <YAWN/GraphicsDevice.hpp>
#include <YAWN/Settings.hpp>
#include <YAWN/IdPool.hpp>
#include <YAWN/Math.hpp>

#include "CommonSDL2.hpp"

namespace YAWN {
    class GraphicsDeviceSDL2 : public GraphicsDeviceImpl {
    public:
        struct CanvasItem {
            Array<SDL_Vertex> Vertices;
            SDL_Rect Source = { 0, 0, 0, 0 };
            SDL_FRect Destination = { 0.0f, 0.0f, 0.0f, 0.0f };
            SDL_FPoint Center = { 0.0f, 0.0f };
            float64 Angle = 0.0f;
            int32 Layer = 0;
            Id TextureId = None;
        };

    public:
        GraphicsDeviceSDL2();

        ~GraphicsDeviceSDL2();

        Id CreateCanvasItem() override;

        void DestroyCanvasItem(Id id) override;

        void SetCanvasItemPrimitives(Id id, const Vector2* positions, const Color* colors, const Vector2* texcoords, usize size) override;

        void SetCanvasItemLayer(Id id, int32 layer) override;

        void SetCanvasItemTexture(Id id, Id textureId) override;

        Id CreateTexture() override;

        void DestroyTexture(Id id) override;

        void SetTextureData(Id id, const uint8* data, int32 width, int32 height) override;

        void Present() override;

    private:
        SDL_Renderer* _renderer;
        Color _clearColor;

        IdPool _canvasItemPool;
        IdPool _textureIdPool;

        Array<CanvasItem> _canvasItems;
        Array<SDL_Texture*> _textures;

        Array<usize> _canvasItemsSortedIndices;
        bool _canvasItemsSortedIndicesDirty = true;
    };
}
