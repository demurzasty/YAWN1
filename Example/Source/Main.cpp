#include <YAWN/YAWN.hpp>

using namespace YAWN;

class AnimatedSprite : public Sprite {
public:
    virtual void Update(float32 timeStep) override {
        Sprite::Update(timeStep);

        static int32 frame = 0;
        SetFrame((frame / 4) % 4);

        frame++;
    }
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
