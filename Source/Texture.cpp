#include <YAWN/Texture.hpp>
#include <YAWN/GraphicsDevice.hpp>

using namespace YAWN;

Managed<Texture> Texture::FromFile(const String& filename) {
    Managed<Image> image = Image::FromFile(filename);
    CheckReturnValue(image, nullptr, "Cannot load texture from: %s.", filename.CStr());
    return FromImage(image);
}

Managed<Texture> Texture::FromImage(Image* image) {
    CheckReturnValue(image, nullptr, "No input image.");

    Managed<Texture> texture = new Texture();
    texture->SetData(image->Data(), image->Width(), image->Height());
    return texture;
}

Texture::Texture()
    : GraphicsResource(GraphicsDevice::CreateTexture()) {
}

Texture::~Texture() {
    GraphicsDevice::DestroyTexture(Id());
}

void Texture::SetData(const uint8* data, int32 width, int32 height) {
    GraphicsDevice::SetTextureData(Id(), data, width, height);

    _width = width;
    _height = height;
}

int32 Texture::Width() const {
    return _width;
}

int32 Texture::Height() const {
    return _height;
}