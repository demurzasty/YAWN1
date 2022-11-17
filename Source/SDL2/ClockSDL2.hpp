#pragma once

#include <YAWN/Clock.hpp>

#include "CommonSDL2.hpp"

namespace YAWN {
    class ClockSDL2 : public ClockImpl {
    public:
        float32 Reset() override;

    private:
        uint64 _currentTime = SDL_GetPerformanceCounter();
        uint64 _lastTime = 0;
    };
}
