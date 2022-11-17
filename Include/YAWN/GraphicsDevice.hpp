#pragma once 

#include "Managed.hpp"
#include "Platform.hpp"
#include "Mutex.hpp"
#include "Vector2.hpp"

namespace YAWN {
    class GraphicsDeviceImpl : public NonCopyable {
    public:
        virtual ~GraphicsDeviceImpl() = default;

        virtual Id CreateCanvasItem() = 0;

        virtual void DestroyCanvasItem(Id id) = 0;

        virtual void SetCanvasItemSource(Id id, int32 x, int32 y, int32 width, int32 height) = 0;

        virtual void SetCanvasItemDestination(Id id, float32 x, float32 y, float32 width, float32 height) = 0;

        virtual void SetCanvasItemCenter(Id id, float32 x, float32 y) = 0;

        virtual void SetCanvasItemRotation(Id id, float32 rotation) = 0;

        virtual void SetCanvasItemLayer(Id id, int32 layer) = 0;

        virtual void SetCanvasItemTexture(Id id, Id textureId) = 0;

        virtual Id CreateTexture() = 0;

        virtual void DestroyTexture(Id id) = 0;

        virtual void SetTextureData(Id id, const uint8* data, int32 width, int32 height) = 0;

        virtual void Present() = 0;
    };

    class GraphicsDevice : public NonInstantiable {
    public:
        static void Initialize();

        static void Release();

        static Id CreateCanvasItem();

        static void DestroyCanvasItem(Id id);

        static void SetCanvasItemSource(Id id, int32 x, int32 y, int32 width, int32 height);

        static void SetCanvasItemDestination(Id id, float32 x, float32 y, float32 width, float32 height);

        static void SetCanvasItemCenter(Id id, float32 x, float32 y);

        static void SetCanvasItemRotation(Id id, float32 rotation);

        static void SetCanvasItemLayer(Id id, int32 layer);

        static void SetCanvasItemTexture(Id id, Id textureId);

        static Id CreateTexture();

        static void DestroyTexture(Id id);

        static void SetTextureData(Id id, const uint8* data, int32 width, int32 height);

        static void Present();

    private:
        static GraphicsDeviceImpl* _impl;
        static Mutex _mutex;
    };
}
