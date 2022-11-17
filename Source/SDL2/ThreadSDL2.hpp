#pragma once 

#include <YAWN/Thread.hpp>

#include "CommonSDL2.hpp"

namespace YAWN {
    class ThreadSDL2 : public ThreadImpl {
    public:
        ThreadSDL2(Function<void()> function);

        ~ThreadSDL2();

    private:
        SDL_Thread* _thread = nullptr;
    };
}
