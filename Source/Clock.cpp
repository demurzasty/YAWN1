#include <YAWN/Clock.hpp>

#include "SDL2/ClockSDL2.hpp"

using namespace YAWN;

Clock::Clock() {
    _impl = new ClockSDL2();
}

Clock::~Clock() {
    delete _impl;
}

float32 Clock::Reset() {
    return _impl->Reset();
}
