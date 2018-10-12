#include "Globals.h"

const float Globals::PI = 3.14159f;

// Useful for me as a dev
bool Globals::debugging = true;

int Globals::screenWidth = 640, Globals::screenHeight = 352, Globals::screenScale = 2;
SDL_Renderer* Globals::renderer = NULL;
