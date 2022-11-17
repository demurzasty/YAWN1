#include "GraphicsDeviceSDL2.hpp"

using namespace YAWN;

GraphicsDeviceSDL2::GraphicsDeviceSDL2()
    : _canvasItems(1024), _textures(1024) {
    CommonSDL2::Retain();

    _renderer = SDL_CreateRenderer((SDL_Window*)Platform::WindowHandle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderSetLogicalSize(_renderer, 320, 180);
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
    _canvasItems[index].Angle = rotation * 57.295779513082320876798154814105;

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
    if (!_textures[index]) {
        _textures[index] = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        CheckReturn(_textures[index], "Cannot create texture: %s.", SDL_GetError());
    }

    int32 result = SDL_UpdateTexture(_textures[index], nullptr, data, width * 4);
    CheckReturn(result == 0, "Cannot update texture: %s.", SDL_GetError());

    SDL_SetTextureBlendMode(_textures[index], SDL_BLENDMODE_BLEND);
}

void GraphicsDeviceSDL2::Present() {
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

        if (_canvasItemsSortedIndices.Size() > 0) {
            for (usize i = 0; i < _canvasItemsSortedIndices.Size() - 1; i++) {
                for (usize j = 0; j < _canvasItemsSortedIndices.Size() - i - 1; j++) {
                    if (_canvasItems[_canvasItemsSortedIndices[j]].Layer > _canvasItems[_canvasItemsSortedIndices[j + 1]].Layer) {
                        usize temp = _canvasItemsSortedIndices[j];
                        _canvasItemsSortedIndices[j] = _canvasItemsSortedIndices[j + 1];
                        _canvasItemsSortedIndices[j + 1] = temp;
                    }
                }
            }
        }

        _canvasItemsSortedIndicesDirty = false;
    }

    for (usize canvasItemIndex : _canvasItemsSortedIndices) {
        CanvasItem& canvasItem = _canvasItems[canvasItemIndex];
        if (canvasItem.TextureId != None) {
            usize textureIndex = usize(canvasItem.TextureId);
            if (_textures[textureIndex]) {
                //if (canvasItem.Dirty) {
                //    int32 width, height;
                //    SDL_QueryTexture(_textures[textureIndex], nullptr, nullptr, &width, &height);

                //    int32 frameWidth = width / canvasItem.HorizontalFrames;
                //    int32 frameHeight = height / canvasItem.VerticalFrames;

                //    canvasItem.SourceRectangle.x = (canvasItem.Frame % canvasItem.HorizontalFrames) * frameWidth;
                //    canvasItem.SourceRectangle.y = (canvasItem.Frame / canvasItem.HorizontalFrames) * frameHeight;
                //    canvasItem.SourceRectangle.w = frameWidth;
                //    canvasItem.SourceRectangle.h = frameHeight;

                //    canvasItem.Center.x = canvasItem.Offset.X * canvasItem.Scale.X;
                //    canvasItem.Center.y = canvasItem.Offset.Y * canvasItem.Scale.Y;

                //    canvasItem.DestinationRectangle.x = canvasItem.Position.X - canvasItem.Center.x;
                //    canvasItem.DestinationRectangle.y = canvasItem.Position.Y - canvasItem.Center.y;
                //    canvasItem.DestinationRectangle.w = frameWidth * canvasItem.Scale.X;
                //    canvasItem.DestinationRectangle.h = frameHeight * canvasItem.Scale.Y;

                //    canvasItem.Angle = canvasItem.Rotation * 57.295779513082320876798154814105;

                //    canvasItem.Dirty = false;
                //}

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