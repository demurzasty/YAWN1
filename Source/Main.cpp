#include <YAWN/Main.hpp>

#if 0 // TODO: If SDL is not used.
#if _WIN32 
#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return Main(__argc, __argv);
}

#endif
#else
#include <SDL.h>
#endif 

int main(int argc, char* argv[]) {
    return Main(argc, argv);
}

