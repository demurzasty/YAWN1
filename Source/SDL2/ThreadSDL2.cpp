#include "ThreadSDL2.hpp"

using namespace YAWN;

static int ThreadFunction(void* userData) {
    Function<void()>* function = (Function<void()>*)userData;
    if (function->CanInvoke()) {
        function->Invoke();
    }
    return 0;
}

ThreadSDL2::ThreadSDL2(Function<void()> function)
    : ThreadImpl(function) {
    _thread = SDL_CreateThread(&ThreadFunction, nullptr, &_function);
}

ThreadSDL2::~ThreadSDL2() {
    SDL_WaitThread(_thread, nullptr);
}
