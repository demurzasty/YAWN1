#include "GraphicsDeviceSDL2.hpp"

using namespace YAWN;

GraphicsDeviceSDL2::GraphicsDeviceSDL2()
    : _canvasItems(1024), _textures(1024), _clearColor(Settings::CanvasClearColor()) {
    CommonSDL2::Retain();

    SDL_Window* window = (SDL_Window*)Platform::WindowHandle();
    uint32 rendererFlags = SDL_RENDERER_ACCELERATED;

    if (Settings::VerticalSynchronization()) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    _renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    int32 canvasWidth = Settings::CanvasWidth();
    int32 canvasHeight = Settings::CanvasHeight();

    SDL_RenderSetLogicalSize(_renderer, canvasWidth, canvasHeight);
}

GraphicsDeviceSDL2::~GraphicsDeviceSDL2() {
    for (SDL_Texture* texture : _textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    SDL_DestroyRenderer(_renderer);

    CommonSDL2::Release();
}

Id GraphicsDeviceSDL2::CreateCanvasItem() {
    _canvasItemsSortedIndicesDirty = true;
    return _canvasItemPool.Acquire();
}

void GraphicsDeviceSDL2::DestroyCanvasItem(Id id) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].TextureId = None;
    _canvasItemsSortedIndicesDirty = true;

    _canvasItemPool.Dispose(id);
}

void GraphicsDeviceSDL2::SetCanvasItemSource(Id id, int32 x, int32 y, int32 width, int32 height) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].Source = { x, y, width, height };

}

void GraphicsDeviceSDL2::SetCanvasItemDestination(Id id, float32 x, float32 y, float32 width, float32 height) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].Destination = { x, y, width, height };
}

void GraphicsDeviceSDL2::SetCanvasItemCenter(Id id, float32 x, float32 y) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].Center = { x, y };

}

void GraphicsDeviceSDL2::SetCanvasItemRotation(Id id, float32 rotation) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].Angle = Math::RadiansToDegrees(rotation);

}

void GraphicsDeviceSDL2::SetCanvasItemLayer(Id id, int32 layer) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].Layer = layer;

    _canvasItemsSortedIndicesDirty = true;
}

void GraphicsDeviceSDL2::SetCanvasItemTexture(Id id, Id textureId) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");

    usize index = usize(id);
    _canvasItems[index].TextureId = textureId;
}

Id GraphicsDeviceSDL2::CreateTexture() {
    return _textureIdPool.Acquire();
}

void GraphicsDeviceSDL2::DestroyTexture(Id id) {
    CheckReturn(_textureIdPool.IsValid(id), "Texture is not valid.");

    usize index = usize(id);
    if (_textures[index]) {
        SDL_DestroyTexture(_textures[index]);
        _textures[index] = nullptr;
    }

    _textureIdPool.Dispose(id);
}

void GraphicsDeviceSDL2::SetTextureData(Id id, const uint8* data, int32 width, int32 height) {
    CheckReturn(_textureIdPool.IsValid(id), "Texture is not valid.");

    usize index = usize(id);
    if (_textures[index]) {
        SDL_DestroyTexture(_textures[index]);
    }

    _textures[index] = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    CheckReturn(_textures[index], "Cannot create texture: %s.", SDL_GetError());

    int32 result = SDL_UpdateTexture(_textures[index], nullptr, data, width * 4);
    CheckReturn(result == 0, "Cannot update texture: %s.", SDL_GetError());

    SDL_SetTextureBlendMode(_textures[index], SDL_BLENDMODE_BLEND);
}

void GraphicsDeviceSDL2::Present() {
    SDL_SetRenderDrawColor(_renderer, _clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
    SDL_RenderClear(_renderer);

    if (_canvasItemsSortedIndicesDirty) {
        _canvasItemsSortedIndices.Clear();

        for (usize i = 0; i < _canvasItems.Size(); ++i) {
            if (_canvasItems[i].TextureId != None) {
                usize textureIndex = usize(_canvasItems[i].TextureId);
                if (_textures[textureIndex]) {
                    _canvasItemsSortedIndices.PushBack(i);
                }
            }
        }

        _canvasItemsSortedIndices.Sort([this](usize indexA, usize indexB) {
            return _canvasItems[indexA].Layer > _canvasItems[indexB].Layer;
        });

        _canvasItemsSortedIndicesDirty = false;
    }

    for (usize canvasItemIndex : _canvasItemsSortedIndices) {
        CanvasItem& canvasItem = _canvasItems[canvasItemIndex];
        if (canvasItem.TextureId != None) {
            usize textureIndex = usize(canvasItem.TextureId);
            if (_textures[textureIndex]) {
                SDL_RenderCopyExF(_renderer,
                    _textures[textureIndex],
                    &canvasItem.Source,
                    &canvasItem.Destination,
                    canvasItem.Angle,
                    &canvasItem.Center,
                    SDL_FLIP_NONE);
            }
        }
    }

    SDL_RenderPresent(_renderer);
}