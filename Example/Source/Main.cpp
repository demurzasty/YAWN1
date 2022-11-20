#include <YAWN/YAWN.hpp>

using namespace YAWN;

class AnimatedSprite : public Sprite {
public:
    virtual void Update(float32 timeStep) override {
        Sprite::Update(timeStep);

        _time += timeStep;
        while (_time > 0.1f) {
            SetFrame((Frame() + 1) % 4);
            _time -= 0.1f;
        }

        SetRotation(Rotation() + timeStep);
    }

private:
    float32 _time = 0.0f;
};

static void Startup() {
    Sprite* sprite = new AnimatedSprite();
    sprite->SetTexture(Texture::FromFile("Data/DinoSpritesVita.png"));
    sprite->SetPosition(Vector2(160.0f, 90.0f));
    sprite->SetOffset(Vector2(12.0f, 24.0f));
    sprite->SetHorizontalFrames(24);
    sprite->SetVerticalFrames(1);
    Scene::Root()->AddChild(sprite);
}

int Main(int argc, char* argv[]) {
    Application::Setup();

    Application::OnStartup(&Startup);

    Application::Run();
    return 0;
}
