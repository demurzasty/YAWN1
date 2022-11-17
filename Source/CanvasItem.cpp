#include <YAWN/CanvasItem.hpp>
#include <YAWN/GraphicsDevice.hpp>

using namespace YAWN;

CanvasItem::CanvasItem() {
    _handle = GraphicsDevice::CreateCanvasItem();
}

CanvasItem::~CanvasItem() {
    GraphicsDevice::DestroyCanvasItem(_handle);
}

Id CanvasItem::Handle() const {
    return _handle;
}

void CanvasItem::SetLayer(int32 layer) {
    _layer = layer;

    GraphicsDevice::SetCanvasItemLayer(_handle, _layer);
}

int32 CanvasItem::Layer() const {
    return _layer;
}

void CanvasItem::SetVisible(bool visible) {
    _visible = visible;

    // GraphicsDevice::SetCanvasItemVisible(_handle, _visible);
}

void CanvasItem::Show() {
    SetVisible(true);
}

void CanvasItem::Hide() {
    SetVisible(false);
}

bool CanvasItem::Visible() const {
    return _visible;
}
