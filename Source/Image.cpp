#include <YAWN/Image.hpp>

#include <stb_image.h>

using namespace YAWN;

Image* Image::FromFile(const String& filename) {
    int32 width, height, components;
    stbi_uc* data = stbi_load(filename.CStr(), &width, &height, &components, STBI_rgb_alpha);
    CheckReturnValue(data, nullptr, "Cannot load image: %s.", filename.CStr());
    return new Image(data, width, height);
}

Image::~Image() {
    stbi_image_free(_data);
}

const uint8* Image::Data() const {
    return _data;
}

int32 Image::Width() const {
    return _width;
}

int32 Image::Height() const {
    return _height;
}

Image::Image(uint8* data, int32 width, int32 height)
    : _data(data), _width(width), _height(height) {
}
