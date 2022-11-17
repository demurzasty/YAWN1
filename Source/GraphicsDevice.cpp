#include <YAWN/GraphicsDevice.hpp>

#include "SDL2/GraphicsDeviceSDL2.hpp"

using namespace YAWN;

GraphicsDeviceImpl* GraphicsDevice::_impl = nullptr;
Mutex GraphicsDevice::_mutex;

void GraphicsDevice::Initialize() {
    _impl = new GraphicsDeviceSDL2();
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

void GraphicsDevice::SetCanvasItemSource(Id id, int32 x, int32 y, int32 width, int32 height) {
    Lock lock(_mutex);

    _impl->SetCanvasItemSource(id, x, y, width, height);
}

void GraphicsDevice::SetCanvasItemDestination(Id id, float32 x, float32 y, float32 width, float32 height) {
    Lock lock(_mutex);

    _impl->SetCanvasItemDestination(id, x, y, width, height);
}

void GraphicsDevice::SetCanvasItemCenter(Id id, float32 x, float32 y) {
    Lock lock(_mutex);

    _impl->SetCanvasItemCenter(id, x, y);
}

void GraphicsDevice::SetCanvasItemRotation(Id id, float32 rotation) {
    Lock lock(_mutex);

    _impl->SetCanvasItemRotation(id, rotation);
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
