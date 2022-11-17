#include <YAWN/Platform.hpp>

#include "SDL2/PlatformSDL2.hpp"

using namespace YAWN;

PlatformImpl* Platform::_impl = nullptr;

void Platform::Initialize() {
    _impl = new PlatformSDL2();
}

void Platform::Release() {
    delete _impl;
}

void Platform::DispatchEvents() {
    _impl->DispatchEvents();
}

bool Platform::IsOpen() {
    return _impl->IsOpen();
}

void* Platform::WindowHandle() {
    return _impl->WindowHandle();
}
