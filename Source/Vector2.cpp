#include <YAWN/Vector2.hpp>

using namespace YAWN;

Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
Vector2 Vector2::One = Vector2(1.0f, 1.0f);
Vector2 Vector2::Up = Vector2(0.0f, -1.0f);
Vector2 Vector2::Down = Vector2(0.0f, 1.0f);
Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
Vector2 Vector2::Right = Vector2(1.0f, 0.0f);

Vector2::Vector2(float scalar)
    : X(scalar), Y(scalar) {
}

Vector2 Vector2::operator+(const Vector2& vector) const {
    return Vector2(X + vector.X, Y + vector.Y);
}

Vector2 Vector2::operator*(const Vector2& vector) const {
    return Vector2(X * vector.X, Y * vector.Y);
}

Vector2 Vector2::operator*(float32 scalar) const {
    return Vector2(X * scalar, Y * scalar);
}

Vector2 Vector2::RotateAroundPoint(const Vector2& point, float32 radians) const {
    const float32 s = Math::Sin(radians);
    const float32 c = Math::Cos(radians);

    Vector2 temp(X - point.X, Y - point.Y);

    float32 x = temp.X * c - temp.Y * s;
    float32 y = temp.X * s + temp.Y * c;

    return Vector2(x + point.X, y + point.Y);
}
