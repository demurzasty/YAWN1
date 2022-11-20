#include <YAWN/Platform.hpp>

#ifdef YAWN_SDL2
#include "SDL2/PlatformSDL2.hpp"
#endif

using namespace YAWN;

PlatformImpl* Platform::_impl = nullptr;

void Platform::Initialize() {
#ifdef YAWN_SDL2
    _impl = new PlatformSDL2();
#endif
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

bool Platform::OpenURL(const String& url) {
    return _impl->OpenURL(url);
}
