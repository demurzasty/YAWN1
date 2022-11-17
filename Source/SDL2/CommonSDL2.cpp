#include "CommonSDL2.hpp"

#include <stdio.h>

using namespace YAWN;

static isize counter = 0;

void CommonSDL2::Retain() {
    if (counter++ == 0) {
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    main;
}

void CommonSDL2::Release() {
    if (--counter == 0) {
        SDL_Quit();
    }
}
