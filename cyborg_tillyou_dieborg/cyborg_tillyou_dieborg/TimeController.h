#ifndef TIMECONTROLLER
#define TIMECONTROLLER

#include<iostream>
#include "SDL.h"

class TimeController {
public:
	static const int PLAY_STATE, PAUSE_STATE;

	int timeState;
	// Last time we checked how many ticks we were up to
	Uint32 lastUpdate;
	// Time since the last frame was renderered onto the screen
	float deltaTimeInSeconds;

	TimeController();
	void update_time(); 
	void pause();
	void resume();
	void reset();

	static TimeController timeController;
};

#endif

