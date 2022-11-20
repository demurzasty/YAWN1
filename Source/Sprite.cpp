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
    CanvasItem::LateUpdate(timeStep);

    if (_dirty) {
        if (Texture()) {
            int32 textureWidth = Texture()->Width();
            int32 textureHeight = Texture()->Height();

            int32 frameWidth = textureWidth / HorizontalFrames();
            int32 frameHeight = textureHeight / VerticalFrames();

            float32 offsetX = Offset().X * Scale().X;
            float32 offsetY = Offset().Y * Scale().Y;

            float32 destinationX = Position().X - offsetX;
            float32 destinationY = Position().Y - offsetY;
            float32 destinationWidth = frameWidth * Scale().X;
            float32 destinationHeight = frameHeight * Scale().Y;

            float32 centerX = Position().X;
            float32 centerY = Position().Y;

            int32 sourceX = (Frame() % HorizontalFrames()) * frameWidth;
            int32 sourceY = (Frame() / HorizontalFrames()) * frameHeight;
            int32 sourceWidth = frameWidth;
            int32 sourceHeight = frameHeight;

            Vector2 positions[6] = {
                Vector2(destinationX, destinationY),
                Vector2(destinationX, destinationY + destinationHeight),
                Vector2(destinationX + destinationWidth, destinationY + destinationHeight),

                Vector2(destinationX + destinationWidth, destinationY + destinationHeight),
                Vector2(destinationX + destinationWidth, destinationY),
                Vector2(destinationX, destinationY),
            };

            for (Vector2& position : positions) {
                position = position.RotateAroundPoint(Position(), Rotation());
            }

            Color colors[6] = {
                Color::White,
                Color::White,
                Color::White,

                Color::White,
                Color::White,
                Color::White,
            };

            Vector2 texcoords[6] = {
                Vector2(float32(sourceX) / textureWidth, float32(sourceY) / textureHeight),
                Vector2(float32(sourceX) / textureWidth, float32(sourceY + sourceHeight) / textureHeight),
                Vector2(float32(sourceX + sourceWidth) / textureWidth, float32(sourceY + sourceHeight) / textureHeight),

                Vector2(float32(sourceX + sourceWidth) / textureWidth, float32(sourceY + sourceHeight) / textureHeight),
                Vector2(float32(sourceX + sourceWidth) / textureWidth, float32(sourceY) / textureHeight),
                Vector2(float32(sourceX) / textureWidth, float32(sourceY) / textureHeight),
            };

            GraphicsDevice::SetCanvasItemPrimitives(_id, positions, colors, texcoords, 6);
            GraphicsDevice::SetCanvasItemTexture(_id, Texture()->Id());
        } else {
            GraphicsDevice::SetCanvasItemPrimitives(_id, nullptr, nullptr, nullptr, 0);
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
