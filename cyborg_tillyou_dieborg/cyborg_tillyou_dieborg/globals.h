#ifndef GLOBALS
#define GLOBALS

#include<string>
#include<iostream>
#include<SDL.h>
#include "random_number.h"

class Globals {
public:
	// Math helper
	static const float PI;

	// Useful for me as a dev
	static bool debugging;
	
	static int ScreenWidth, ScreenHeight, ScreenScale;
	static SDL_Renderer* renderer;

};

#endif


