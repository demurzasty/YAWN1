#include "ClockSDL2.hpp"

#include <stdio.h>

using namespace YAWN;

static uint64 PerformanceFrequency() {
    static uint64 performanceFrequency = SDL_GetPerformanceFrequency();
    return performanceFrequency;
}

float32 ClockSDL2::Reset() {
    _lastTime = _currentTime;
    _currentTime = SDL_GetPerformanceCounter();
    return float32((_currentTime - _lastTime) * 1.0L / PerformanceFrequency());
}
