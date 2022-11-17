#pragma once 

#include "Managed.hpp"

namespace YAWN {
    class PlatformImpl : public NonCopyable {
    public:
        virtual ~PlatformImpl() = default;

        virtual void DispatchEvents() = 0;

        virtual bool IsOpen() const = 0;

        virtual void* WindowHandle() const = 0;
    };

    class Platform : public NonInstantiable {
    public:
        static void Initialize();

        static void Release();

        static void DispatchEvents();

        static bool IsOpen();

        static void* WindowHandle();

    private:
        static PlatformImpl* _impl;
    };
}
