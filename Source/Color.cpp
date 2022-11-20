#include <YAWN/Color.hpp>

using namespace YAWN;

Color Color::White = Color(255, 255, 255);
Color Color::Black = Color(0, 0, 0);
Color Color::Transparent = Color(0, 0, 0, 0);
Color Color::Red = Color(255, 0, 0);
Color Color::Green = Color(0, 255, 0);
Color Color::Blue = Color(0, 0, 255);
Color Color::CornflowerBlue = Color(100, 149, 237);

Color::Color(uint8 r, uint8 g, uint8 b, uint8 a)
    : R(r), G(g), B(b), A(a) {
}
