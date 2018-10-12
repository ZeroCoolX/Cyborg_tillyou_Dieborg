#ifndef FRAME
#define FRAME

#include<iostream>
#include<list>
#include<fstream>
#include<sstream>
#include "SDL.h"
#include "DrawingFunctions.h"
#include "Globals.h"
#include "GroupBuilder.h"

using namespace std;

class Frame {
public:
	int frameNumber; // or index
	SDL_Rect clip; // Its the region of the spritesheet where this frame is
	float duration; // how long the frame runs for
	SDL_Point offset; // Pivot point to help align frames in animation

	list<Group*> frameData; // Holds groups of additional data for the frame

	void draw(SDL_Texture* spriteSheet, float x, float y);

	// TODO load_frame
};

#endif // !FRAME
