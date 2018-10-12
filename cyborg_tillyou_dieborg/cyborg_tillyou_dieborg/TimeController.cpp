#include "TimeController.h"

const int TimeController::PLAY_STATE = 0, TimeController::PAUSE_STATE = 1;

TimeController::TimeController():deltaTimeInSeconds(0), lastUpdate(0)
{
	timeState = PLAY_STATE;
}

void TimeController::update_time()
{
	if (timeState == PAUSE_STATE) {
		deltaTimeInSeconds = 0;
	}
	else {
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		deltaTimeInSeconds = timeDiff / 1000.0; // Move miliseconds into the decimal place area e.g. 104 = 0.104s
	}
	lastUpdate = SDL_GetTicks();
}

void TimeController::pause()
{
	timeState = PAUSE_STATE;
}

void TimeController::resume()
{
	timeState = PLAY_STATE;
}

void TimeController::reset()
{
	deltaTimeInSeconds = 0;
	lastUpdate = SDL_GetTicks();
}

// Builds a global TimeController object for use anywhere
TimeController TimeController::timeController;


