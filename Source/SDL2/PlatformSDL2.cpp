#include "PlatformSDL2.hpp"

#ifdef _WIN32

#include <Windows.h>

static void SetProcessDpiAware() {
	HINSTANCE shCoreDll = LoadLibrary("Shcore.dll");
	if (shCoreDll) {
		enum ProcessDpiAwareness {
			ProcessDpiUnaware = 0,
			ProcessSystemDpiAware = 1,
			ProcessPerMonitorDpiAware = 2
		};

		typedef HRESULT(WINAPI* SetProcessDpiAwarenessFuncType)(ProcessDpiAwareness);
		SetProcessDpiAwarenessFuncType SetProcessDpiAwarenessFunc = reinterpret_cast<SetProcessDpiAwarenessFuncType>(GetProcAddress(shCoreDll, "SetProcessDpiAwareness"));

		if (SetProcessDpiAwarenessFunc) {
			if (SetProcessDpiAwarenessFunc(ProcessSystemDpiAware) != E_INVALIDARG) {
				FreeLibrary(shCoreDll);
				return;
			}
		}

		FreeLibrary(shCoreDll);
	}

	HINSTANCE user32Dll = LoadLibrary("user32.dll");
	if (user32Dll) {
		typedef BOOL(WINAPI* SetProcessDPIAwareFuncType)(void);
		SetProcessDPIAwareFuncType SetProcessDPIAwareFunc = reinterpret_cast<SetProcessDPIAwareFuncType>(GetProcAddress(user32Dll, "SetProcessDPIAware"));

		if (SetProcessDPIAwareFunc) {
			SetProcessDPIAwareFunc();
		}

		FreeLibrary(user32Dll);
	}
}
#else
static void SetProcessDpiAware() {}
#endif


using namespace YAWN;

PlatformSDL2::PlatformSDL2() {
	SetProcessDpiAware();

    CommonSDL2::Retain();
    
    _window = SDL_CreateWindow("YAWN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_ALLOW_HIGHDPI);
}

PlatformSDL2::~PlatformSDL2() {
    SDL_DestroyWindow(_window);

    CommonSDL2::Release();
}

void PlatformSDL2::DispatchEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _open = false;
        }
    }
}

bool PlatformSDL2::IsOpen() const {
    return _open;
}

void* PlatformSDL2::WindowHandle() const {
    return _window;
}

