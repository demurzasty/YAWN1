#include <YAWN/Mutex.hpp>
#include <YAWN/Error.hpp>

#include "SDL2/MutexSDL2.hpp"

using namespace YAWN;

Mutex::Mutex() {
    _impl = new MutexSDL2();
}

Mutex::~Mutex() {
    delete _impl;
}

void Mutex::Lock() {
    _impl->Lock();
}

bool Mutex::TryLock() {
    return _impl->TryLock();
}

void Mutex::Unlock() {
    _impl->Unlock();
}

Lock::Lock(Mutex& mutex)
    : _mutex(mutex) {
    _mutex.Lock();
}

Lock::~Lock() {
    _mutex.Unlock();
}
