#pragma once 

#include "Managed.hpp"
#include "String.hpp"

namespace YAWN {
    class PlatformImpl : public NonCopyable {
    public:
        virtual ~PlatformImpl() = default;

        virtual void DispatchEvents() = 0;

        virtual bool IsOpen() const = 0;

        virtual void* WindowHandle() const = 0;

        virtual bool OpenURL(const String& url) const = 0;
    };

    class Platform : public NonInstantiable {
    public:
        static void Initialize();

        static void Release();

        static void DispatchEvents();

        static bool IsOpen();

        static void* WindowHandle();

        static bool OpenURL(const String& url);

    private:
        static PlatformImpl* _impl;
    };
}
