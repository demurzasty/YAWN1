#pragma once 

#include <YAWN/Platform.hpp>
#include <YAWN/Settings.hpp>

#include "CommonSDL2.hpp"

namespace YAWN {
    class PlatformSDL2 : public PlatformImpl {
    public:
        PlatformSDL2();

        ~PlatformSDL2();

        void DispatchEvents() override;

        bool IsOpen() const override;

        void* WindowHandle() const override;

        bool OpenURL(const String& url) const override;

    private:
        SDL_Window* _window = nullptr;
        bool _open = true;
    };
}