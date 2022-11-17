#include "MutexSDL2.hpp"

using namespace YAWN;

MutexSDL2::MutexSDL2() {
    _mutex = SDL_CreateMutex();
}

MutexSDL2::~MutexSDL2() {
    SDL_DestroyMutex(_mutex);
}

void MutexSDL2::Lock() {
    SDL_LockMutex(_mutex);
}

bool MutexSDL2::TryLock() {
    return SDL_TryLockMutex(_mutex) != SDL_MUTEX_TIMEDOUT;
}

void MutexSDL2::Unlock() {
    SDL_UnlockMutex(_mutex);
}
