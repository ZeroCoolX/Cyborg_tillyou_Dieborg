#include "globals.h"

const float Globals::PI = 3.14159;

// Useful for me as a dev
bool Globals::debugging = true;

int Globals::ScreenWidth = 640, Globals::ScreenHeight = 352, Globals::ScreenScale = 2;
SDL_Renderer* Globals::renderer = NULL;