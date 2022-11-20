#pragma once 

#include "CanvasItem.hpp"
#include "Texture.hpp"

namespace YAWN {
    class Sprite : public CanvasItem {
    public:
        Sprite();

        virtual ~Sprite();

        virtual void LateUpdate(float32 timeStep) override;

        void SetTexture(Managed<Texture> texture);

        const Managed<Texture>& Texture();

        void SetOffset(const Vector2& offset);

        const Vector2& Offset() const;

        void SetHorizontalFrames(int32 horizontalFrames);

        int32 HorizontalFrames() const;

        void SetVerticalFrames(int32 verticalFrames);

        int32 VerticalFrames() const;

        void SetFrame(int32 frame);

        int32 Frame() const;

    private:
        Id _id = None;
        Managed<YAWN::Texture> _texture;
        Vector2 _offset = Vector2::Zero;
        int32 _horizontalFrames = 1;
        int32 _verticalFrames = 1;
        int32 _frame = 0;
        bool _dirty = false;
    };
}