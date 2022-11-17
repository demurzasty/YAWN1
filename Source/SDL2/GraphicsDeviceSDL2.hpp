#pragma once 

#include <YAWN/GraphicsDevice.hpp>
#include <YAWN/IdPool.hpp>

#include "CommonSDL2.hpp"

namespace YAWN {
    class GraphicsDeviceSDL2 : public GraphicsDeviceImpl {
    public:
        struct CanvasItem {
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

        void SetCanvasItemSource(Id id, int32 x, int32 y, int32 width, int32 height) override;

        void SetCanvasItemDestination(Id id, float32 x, float32 y, float32 width, float32 height) override;

        void SetCanvasItemCenter(Id id, float32 x, float32 y) override;

        void SetCanvasItemRotation(Id id, float32 rotation) override;

        void SetCanvasItemLayer(Id id, int32 layer) override;

        void SetCanvasItemTexture(Id id, Id textureId) override;

        Id CreateTexture() override;

        void DestroyTexture(Id id) override;

        void SetTextureData(Id id, const uint8* data, int32 width, int32 height) override;

        void Present() override;

    private:
        SDL_Renderer* _renderer;

        IdPool _canvasItemPool;
        IdPool _textureIdPool;

        Array<CanvasItem> _canvasItems;
        Array<SDL_Texture*> _textures;

        Array<usize> _canvasItemsSortedIndices;
        bool _canvasItemsSortedIndicesDirty = true;
    };
}
