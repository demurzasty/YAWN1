#pragma once 

#include "Core.hpp"

namespace YAWN {
    class Color {
    public:
        Color() = default;

        Color(uint8 r, uint8 g, uint8 b, uint8 a = 255);

        Color(const Color&) = default;

        Color& operator=(const Color&) = default;

    public:
        static Color White;
        static Color Black;
        static Color Transparent;
        static Color Red;
        static Color Green;
        static Color Blue;
        static Color CornflowerBlue;

    public:
        uint8 R;
        uint8 G;
        uint8 B;
        uint8 A;
    };
}
