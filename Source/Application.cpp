#include <YAWN/YAWN.hpp>

using namespace YAWN;

Array<void(*)()> Application::_initializations;
Array<void(*)()> Application::_releases;
Array<Function<void()>> Application::_startups;
Array<Function<void(float)>> Application::_updates;
Array<Function<void(float)>> Application::_fixedUpdates;

void Application::Setup() {
    AddService<Platform>();
    AddService<GraphicsDevice>();
    AddService<Scene>();
}

void Application::Run() {
    for (void(*initialize)() : _initializations) {
        initialize();
    }

    for (const Function<void()>& startup : _startups) {
        startup();
    }

    Clock clock;
    while (Platform::IsOpen()) {
        Platform::DispatchEvents();

        float32 timeStep = clock.Reset();
        for (const Function<void(float)>& update : _updates) {
            update(timeStep);
        }

        Scene::Update(timeStep);

        Scene::FixedUpdate(timeStep);

        Scene::LateUpdate(timeStep);

        GraphicsDevice::Present();
    }

    for (void(*release)() : _releases) {
        release();
    }
}

void Application::OnStartup(Function<void()> startup) {
    _startups.PushBack(startup);
}

void Application::OnUpdate(Function<void(float)> update) {
    _updates.PushBack(update);
}

void Application::OnFixedUpdate(Function<void(float)> fixedUpdate) {
    _fixedUpdates.PushBack(fixedUpdate);
}
