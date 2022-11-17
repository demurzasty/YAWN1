#pragma once 

#include "Node.hpp"
#include "Vector2.hpp"

namespace YAWN {
    class Node2D : public Node {
    public:
        virtual ~Node2D() = default;

        void SetPosition(const Vector2& position);

        const Vector2& Position() const;

        void SetRotation(float32 rotation);

        float32 Rotation() const;

        void SetScale(const Vector2& scale);

        const Vector2& Scale() const;

    private:
        Vector2 _position = Vector2::Zero;
        float32 _rotation = 0.0f;
        Vector2 _scale = Vector2::One;
    };
}
