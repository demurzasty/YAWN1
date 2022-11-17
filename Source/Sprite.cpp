#include <YAWN/Sprite.hpp>
#include <YAWN/GraphicsDevice.hpp>

using namespace YAWN;

Sprite::Sprite() {
    _id = GraphicsDevice::CreateCanvasItem();
}

Sprite::~Sprite() {
    GraphicsDevice::DestroyCanvasItem(_id);
}

void Sprite::LateUpdate(float32 timeStep) {
    Node2D::LateUpdate(timeStep);

    if (_dirty) {
        if (Texture()) {
            int32 textureWidth = Texture()->Width();
            int32 textureHeight = Texture()->Height();

            int32 frameWidth = textureWidth / HorizontalFrames();
            int32 frameHeight = textureHeight / VerticalFrames();

            float32 centerX = Offset().X * Scale().X;
            float32 centerY = Offset().Y * Scale().Y;

            float32 destinationX = Position().X - centerX;
            float32 destinationY = Position().Y - centerY;
            float32 destinationWidth = frameWidth * Scale().X;
            float32 destinationHeight = frameHeight * Scale().Y;

            int32 sourceX = (Frame() % HorizontalFrames()) * frameWidth;
            int32 sourceY = (Frame() / HorizontalFrames()) * frameHeight;
            int32 sourceWidth = frameWidth;
            int32 sourceHeight = frameHeight;

            GraphicsDevice::SetCanvasItemTexture(_id, Texture()->Id());
            GraphicsDevice::SetCanvasItemSource(_id, sourceX, sourceY, sourceWidth, sourceHeight);
            GraphicsDevice::SetCanvasItemDestination(_id, destinationX, destinationY, destinationWidth, destinationHeight);
            GraphicsDevice::SetCanvasItemCenter(_id, centerX, centerY);
            GraphicsDevice::SetCanvasItemRotation(_id, Rotation());
        } else {
            GraphicsDevice::SetCanvasItemTexture(_id, None);
        }

        _dirty = false;
    }
}

void Sprite::SetTexture(YAWN::Texture* texture) {
    _texture = texture;
    _dirty = true;
}

Texture* Sprite::Texture() {
    return _texture;
}

void Sprite::SetOffset(const Vector2& offset) {
    _offset = offset;
    _dirty = true;
}

const Vector2& Sprite::Offset() const {
    return _offset;
}

void Sprite::SetHorizontalFrames(int32 horizontalFrames) {
    _horizontalFrames = horizontalFrames;
    _dirty = true;
}

int32 Sprite::HorizontalFrames() const {
    return _horizontalFrames;
}

void Sprite::SetVerticalFrames(int32 verticalFrames) {
    _verticalFrames = verticalFrames;
    _dirty = true;
}

int32 Sprite::VerticalFrames() const {
    return _verticalFrames;
}

void Sprite::SetFrame(int32 frame) {
    _frame = frame;
    _dirty = true;
}

int32 Sprite::Frame() const {
    return _frame;
}
