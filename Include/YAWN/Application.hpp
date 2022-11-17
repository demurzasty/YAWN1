#pragma once 

#include "Managed.hpp"
#include "Array.hpp"
#include "Function.hpp"

namespace YAWN {
    class Application : public NonInstantiable {
    public:
        static void Setup();

        static void Run();

        template<typename TService>
        static void AddService() {
            _initializations.PushBack(&TService::Initialize);
            _releases.PushFront(&TService::Release);
        }

        static void OnStartup(Function<void()> startup);

        static void OnUpdate(Function<void(float)> update);

        static void OnFixedUpdate(Function<void(float)> fixedUpdate);

    private:
        static Array<void(*)()> _initializations;
        static Array<void(*)()> _releases;
        static Array<Function<void()>> _startups;
        static Array<Function<void(float)>> _updates;
        static Array<Function<void(float)>> _fixedUpdates;
    };
}
