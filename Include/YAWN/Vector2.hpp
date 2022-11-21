#pragma once 

#include "Math.hpp"

namespace YAWN {
    class Vector2 {
    public:
        Vector2() = default;

        explicit Vector2(float32 scalar);

        Vector2(float32 x, float32 y) : X(x), Y(y) {}

        Vector2(const Vector2&) = default;

        Vector2& operator=(const Vector2&) = default;

        Vector2 operator+(const Vector2& vector) const;

        Vector2 operator*(const Vector2& vector) const;

        Vector2 operator*(float32 scalar) const;

        Vector2 RotateAroundPoint(const Vector2& point, float32 radians) const;

    public:
        static Vector2 Zero;
        static Vector2 One;
        static Vector2 Up;
        static Vector2 Down;
        static Vector2 Left;
        static Vector2 Right;

    public:
        float32 X;
        float32 Y;
    };
}
