#pragma once 

#include "Core.hpp"

namespace YAWN {
    class ClockImpl : public NonCopyable {
    public:
        virtual ~ClockImpl() = default;

        virtual float32 Reset() = 0;
    };

    class Clock : public NonCopyable {
    public:
        Clock();

        ~Clock();

        float32 Reset();

    private:
        ClockImpl* _impl = nullptr;
    };
}