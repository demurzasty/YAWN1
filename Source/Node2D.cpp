#include <YAWN/Node2D.hpp>

using namespace YAWN;

void Node2D::SetPosition(const Vector2& position) {
    _position = position;
}

const Vector2& Node2D::Position() const {
    return _position;
}

void Node2D::SetRotation(float32 rotation) {
    _rotation = rotation;
}

float32 Node2D::Rotation() const {
    return _rotation;
}

void Node2D::SetScale(const Vector2& scale) {
    _scale = scale;
}

const Vector2& Node2D::Scale() const {
    return _scale;
}
