#include <YAWN/Node2D.hpp>

using namespace YAWN;

void Node2D::LateUpdate(float32 timeStep) {
    Node::LateUpdate(timeStep);

    if (_dirty) {
        OnTransformChanged();

        _dirty = false;
    }
}

void Node2D::Translate(const Vector2& translation) {
    _position = _position + translation;
    _dirty = true;
}

void Node2D::Rotate(float32 rotation) {
    _rotation += rotation;
    _dirty = true;
}

void Node2D::SetPosition(const Vector2& position) {
    _position = position;
    _dirty = true;
}

const Vector2& Node2D::Position() const {
    return _position;
}

void Node2D::SetRotation(float32 rotation) {
    _rotation = rotation;
    _dirty = true;
}

float32 Node2D::Rotation() const {
    return _rotation;
}

void Node2D::SetScale(const Vector2& scale) {
    _scale = scale;
    _dirty = true;
}

const Vector2& Node2D::Scale() const {
    return _scale;
}

void Node2D::OnTransformChanged() {
}
