#pragma once 

#include "Node2D.hpp"

namespace YAWN {
    class CanvasItem : public Node2D {
    public:
        CanvasItem();

        virtual ~CanvasItem();

        Id Handle() const;

        void SetLayer(int32 layer);

        int32 Layer() const;

        void SetVisible(bool visible);

        void Show();

        void Hide();

        bool Visible() const;

    private:
        Id _handle = None;
        int32 _layer = 0;
        bool _visible = true;
    };
}