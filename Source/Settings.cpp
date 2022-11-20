#include <YAWN/Settings.hpp>

using namespace YAWN;

Map<String, Variant> Settings::_settings;

void Settings::Setup() {
    SetWindowWidth(1280);
    SetWindowHeight(720);
    SetWindowFullscreen(false);
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
    static String title = "YAWN";
    return title;
}

void Settings::SetWindowWidth(int32 width) {
    Set("WindowWidth", width);
}

int32 Settings::WindowWidth() {
    return 1280;
}

void Settings::SetWindowHeight(int32 height) {
    Set("WindowHeight", height);
}

int32 Settings::WindowHeight() {
    return 720;
}

void Settings::SetWindowFullscreen(bool fullscreen) {
    Set("WindowFullscreen", fullscreen);
}

bool Settings::WindowFullscreen() {
    return false;
}

void Settings::SetVerticalSynchronization(bool enable) {
    Set("VerticalSynchronization", enable);
}

bool Settings::VerticalSynchronization() {
    return true;
}

void Settings::SetCanvasWidth(int32 width) {
    Set("CanvasWidth", width);
}

int32 Settings::CanvasWidth() {
    return 320;
}

void Settings::SetCanvasHeight(int32 height) {
    Set("CanvasHeight", height);
}

int32 Settings::CanvasHeight() {
    return 180;
}

void Settings::SetCanvasClearColor(const Color& color) {
    Set("CanvasClearColor", color);
}

Color Settings::CanvasClearColor() {
    return Color::CornflowerBlue;
}