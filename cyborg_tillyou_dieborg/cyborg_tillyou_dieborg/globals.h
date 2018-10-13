#ifndef GLOBALS
#define GLOBALS

#include<iostream>
#include<SDL.h>
#include "RandomNumber.h"
#include<string>

using namespace std;

class Globals {
public:
	// Math helper
	static const float PI;

	// Useful for me as a dev
	static bool debugging;

	static int screenWidth, screenHeight, screenScale;
	static SDL_Renderer* renderer;

	static string clip_off_data_header(string data);
};

#endif
