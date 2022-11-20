#include <YAWN/GraphicsDevice.hpp>

#ifdef YAWN_SDL2
#include "SDL2/GraphicsDeviceSDL2.hpp"
#endif

using namespace YAWN;

GraphicsDeviceImpl* GraphicsDevice::_impl = nullptr;
Mutex GraphicsDevice::_mutex;

void GraphicsDevice::Initialize() {
#ifdef YAWN_SDL2
    _impl = new GraphicsDeviceSDL2();
#endif
}

void GraphicsDevice::Release() {
    delete _impl;
}

Id GraphicsDevice::CreateCanvasItem() {
    Lock lock(_mutex);

    return _impl->CreateCanvasItem();
}

void GraphicsDevice::DestroyCanvasItem(Id id) {
    Lock lock(_mutex);

    _impl->DestroyCanvasItem(id);
}

void GraphicsDevice::SetCanvasItemPrimitives(Id id, const Vector2* positions, const Color* colors, const Vector2* texcoords, usize size) {
    Lock lock(_mutex);

    _impl->SetCanvasItemPrimitives(id, positions, colors, texcoords, size);
}

void GraphicsDevice::SetCanvasItemLayer(Id id, int32 layer) {
    Lock lock(_mutex);

    _impl->SetCanvasItemLayer(id, layer);
}

void GraphicsDevice::SetCanvasItemTexture(Id id, Id textureId) {
    Lock lock(_mutex);

    _impl->SetCanvasItemTexture(id, textureId);
}

Id GraphicsDevice::CreateTexture() {
    Lock lock(_mutex);

    return _impl->CreateTexture();
}

void GraphicsDevice::DestroyTexture(Id id) {
    Lock lock(_mutex);

    _impl->DestroyTexture(id);
}

void GraphicsDevice::SetTextureData(Id id, const uint8* data, int32 width, int32 height) {
    Lock lock(_mutex);

    _impl->SetTextureData(id, data, width, height);
}

void GraphicsDevice::Present() {
    Lock lock(_mutex);

    _impl->Present();
}
