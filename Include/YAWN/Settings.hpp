#pragma once 

#include "Core.hpp"
#include "Map.hpp"
#include "String.hpp"
#include "Variant.hpp"
#include "Color.hpp"

namespace YAWN {
    class Settings : public NonInstantiable {
    public:
        static void Setup();

        static void Set(const String& name, const Variant& value);

        static const Variant& Get(const String& name);

        static void SetWindowTitle(const String& title);

        static const String& WindowTitle();

        static void SetWindowWidth(int32 width);

        static int32 WindowWidth();

        static void SetWindowHeight(int32 height);

        static int32 WindowHeight();

        static void SetWindowFullscreen(bool fullscreen);

        static bool WindowFullscreen();

        static void SetVerticalSynchronization(bool enable);

        static bool VerticalSynchronization();

        static void SetCanvasWidth(int32 width);

        static int32 CanvasWidth();

        static void SetCanvasHeight(int32 height);

        static int32 CanvasHeight();

        static void SetCanvasClearColor(const Color& color);

        static Color CanvasClearColor();

    private:
        static Map<String, Variant> _settings;
    };
}