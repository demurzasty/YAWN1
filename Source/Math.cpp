#include <YAWN/Math.hpp>

#ifdef YAWN_SDL2
#include <SDL.h>

#define sinf SDL_sinf
#define cosf SDL_cosf
#define asinf SDL_asinf 
#define atan2f SDL_atan2f
#define powf SDL_powf
#define logf SDL_logf

#else
#include <math.h>
#endif 

using namespace YAWN;

float32 Math::RadiansToDegrees(float32 radians) {
    return radians * 57.295779513082320876798154814105f;
}

float32 Math::DegreesToRadians(float32 degrees) {
    return degrees * 0.01745329251994329576923690768489f;
}

float32 Math::Sin(float32 radians) {
    return sinf(radians);
}

float32 Math::Cos(float32 radians) {
    return cosf(radians);
}

float32 Math::Asin(float32 radians) {
    return asinf(radians);
}

float32 Math::Atan2(float32 a, float32 b) {
    return atan2f(a, b);
}

float32 Math::Pow(float32 x, float32 y) {
    return powf(x, y);
}

float32 Math::Log(float32 value) {
    return logf(value);
}

usize Math::Align(usize size, usize align) {
    return (size + align - 1) & ~(align - 1);
}

bool Math::IsPowerOfTwo(int32 value) {
    return !(value == 0) && !(value & (value - 1));
}

int32 Math::NextPowerOfTwo(int32 value) {
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return ++value;
}

int32 Math::Abs(int32 value) {
    return value < 0 ? -value : value;
}

float32 Math::Abs(float32 value) {
    (*(uint32*)(&value)) &= 0x7fffffff;
    return value;
}

int32 Math::Max(int32 x, int32 y) {
    return x > y ? x : y;
}

float32 Math::Max(float32 x, float32 y) {
    return x > y ? x : y;
}

int32 Math::Min(int32 x, int32 y) {
    return x < y ? x : y;
}

float32 Math::Min(float32 x, float32 y) {
    return x < y ? x : y;
}

int32 Math::Clamp(int32 value, int32 min, int32 max) {
    return Max(Min(value, max), min);
}

float32 Math::Clamp(float32 value, float32 min, float32 max) {
    return Max(Min(value, max), min);
}
