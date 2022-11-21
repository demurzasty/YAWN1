#include "GraphicsDeviceSDL2.hpp"

using namespace YAWN;

GraphicsDeviceSDL2::GraphicsDeviceSDL2()
    : _canvasItems(8192), _textures(8192), _clearColor(Settings::CanvasClearColor()) {
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

void GraphicsDeviceSDL2::SetCanvasItemPrimitives(Id id, const Vector2* positions, const Color* colors, const Vector2* texcoords, usize size) {
    CheckReturn(_canvasItemPool.IsValid(id), "CanvasItem is not valid.");
    CheckReturn(size == 0 || positions, "You must provide at least positions data of primitives.");

    usize index = usize(id);
    Array<SDL_Vertex>& vertices = _canvasItems[index].Vertices;

    if (size > 0) {
        vertices.Resize(size);
        for (usize i = 0; i < size; ++i) {
            vertices[i].position = { positions[i].X, positions[i].Y };

            if (colors) {
                vertices[i].color = { colors[i].R, colors[i].G, colors[i].B, colors[i].A };
            } else {
                vertices[i].color = { 255, 255, 255, 255 };
            }

            if (texcoords) {
                vertices[i].tex_coord = { texcoords[i].X, texcoords[i].Y };
            } else {
                vertices[i].tex_coord = { 0.0f, 0.0f };
            }
        }
    } else {
        vertices.Clear();
    }
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
                if (canvasItem.Vertices.Size() > 0) {
                    SDL_RenderGeometry(_renderer,
                        _textures[textureIndex],
                        canvasItem.Vertices.Data(),
                        int32(canvasItem.Vertices.Size()),
                        nullptr,
                        0);
                }
            }
        }
    }

    SDL_RenderPresent(_renderer);
}