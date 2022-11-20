#include <YAWN/Settings.hpp>

using namespace YAWN;

Map<String, Variant> Settings::_settings;

void Settings::Setup() {
    SetWindowTitle("YAWN");
    SetWindowWidth(1280);
    SetWindowHeight(720);
    SetWindowFullscreen(false);
    SetVerticalSynchronization(true);
    SetCanvasWidth(320);
    SetCanvasHeight(180);
    SetCanvasClearColor(Color::CornflowerBlue);
}

void Settings::Set(const String& name, const Variant& value) {
    _settings[name] = value;
}

const Variant& Settings::Get(const String& name) {
    return _settings[name];
}

void Settings::SetWindowTitle(const String& title) {
    Set("WindowTitle", title);
}

const String& Settings::WindowTitle() {
    return Get("WindowTitle").String();
}

void Settings::SetWindowWidth(int32 width) {
    Set("WindowWidth", width);
}

int32 Settings::WindowWidth() {
    return Get("WindowWidth");
}

void Settings::SetWindowHeight(int32 height) {
    Set("WindowHeight", height);
}

int32 Settings::WindowHeight() {
    return Get("WindowHeight");
}

void Settings::SetWindowFullscreen(bool fullscreen) {
    Set("WindowFullscreen", fullscreen);
}

bool Settings::WindowFullscreen() {
    return Get("WindowFullscreen");
}

void Settings::SetVerticalSynchronization(bool enable) {
    Set("VerticalSynchronization", enable);
}

bool Settings::VerticalSynchronization() {
    return Get("VerticalSynchronization");
}

void Settings::SetCanvasWidth(int32 width) {
    Set("CanvasWidth", width);
}

int32 Settings::CanvasWidth() {
    return Get("CanvasWidth");
}

void Settings::SetCanvasHeight(int32 height) {
    Set("CanvasHeight", height);
}

int32 Settings::CanvasHeight() {
    return Get("CanvasHeight");
}

void Settings::SetCanvasClearColor(const Color& color) {
    Set("CanvasClearColor", color);
}

Color Settings::CanvasClearColor() {
    return Get("CanvasClearColor");
}