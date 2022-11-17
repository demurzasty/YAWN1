#include <YAWN/Thread.hpp>

#include "SDL2/ThreadSDL2.hpp"

using namespace YAWN;

ThreadImpl::ThreadImpl(Function<void()> function)
    : _function(function) {
}

Thread::Thread(Function<void()> function) {
    _impl = new ThreadSDL2(function);
}

Thread::~Thread() {
    delete _impl;
}

