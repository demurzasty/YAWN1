#pragma once 

#include "Core.hpp"

namespace YAWN {
    class Math : public NonInstantiable {
    public:
        static constexpr float32 Epsilon = 0.00001f;

        constexpr static float32 PI = 3.1415926535897932384626433833f;

        constexpr static float32 TAU = 6.2831853071795864769252867666f;

        static float32 RadiansToDegrees(float32 radians);

        static float32 DegreesToRadians(float32 degrees);

        static float32 Sin(float32 radians);

        static float32 Cos(float32 radians);

        static float32 Asin(float32 radians);

        static float32 Atan2(float32 a, float32 b);

        static float32 Pow(float32 x, float32 y);

        static float32 Log(float32 value);

        static usize Align(usize size, usize align);

        static bool IsPowerOfTwo(int32 value);

        static int32 NextPowerOfTwo(int32 value);

        static int32 Abs(int32 value);

        static float32 Abs(float32 value);

        static int32 Max(int32 x, int32 y);

        static float32 Max(float32 x, float32 y);

        static int32 Min(int32 x, int32 y);

        static float32 Min(float32 x, float32 y);

        static int32 Clamp(int32 value, int32 min, int32 max);

        static float32 Clamp(float32 value, float32 min, float32 max);
    };
}