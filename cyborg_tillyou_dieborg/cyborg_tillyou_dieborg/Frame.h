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
	int m_frameNumber; // or index
	SDL_Rect m_clip; // Its the region of the spritesheet where this frame is
	float m_duration; // how long the frame runs for
	SDL_Point m_offset; // Pivot point to help align frames in animation

	list<Group*> m_frameData; // Holds groups of additional data for the frame

	void draw(SDL_Texture* spriteSheet, float x, float y);
	void load_frame(ifstream& file, list<DataGroupType>& groupTypes);
};

#endif // !FRAME
