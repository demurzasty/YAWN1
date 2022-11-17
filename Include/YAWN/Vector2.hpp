#pragma once 

#include "Core.hpp"

namespace YAWN {
    class Vector2 {
    public:
        Vector2() = default;

        explicit Vector2(float32 scalar) : X(scalar), Y(scalar) {}

        Vector2(float32 x, float32 y) : X(x), Y(y) {}

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
