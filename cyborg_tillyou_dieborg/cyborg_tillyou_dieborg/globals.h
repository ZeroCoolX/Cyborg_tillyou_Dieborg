#ifndef GLOBALS
#define GLOBALS

#include<string>
#include<iostream>
#include<SDL.h>
#include "RandomNumber.h"

class Globals {
public:
	// Math helper
	static const float PI;

	// Useful for me as a dev
	static bool debugging;

	static int screenWidth, screenHeight, screenScale;
	static SDL_Renderer* renderer;

};

#endif
