#pragma once 

#include <YAWN/Mutex.hpp>

#include "CommonSDL2.hpp"

namespace YAWN {
    class MutexSDL2 : public MutexImpl {
    public:
        MutexSDL2();

        ~MutexSDL2();

        void Lock() override;

        bool TryLock() override;

        void Unlock() override;

    private:
        SDL_mutex* _mutex = nullptr;
    };
}