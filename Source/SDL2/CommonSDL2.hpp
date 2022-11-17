#pragma once 

#include <YAWN/Core.hpp>

#include <SDL.h>

namespace YAWN {
    class CommonSDL2 : public NonInstantiable {
    public:
        static void Retain();

        static void Release();
    };
}