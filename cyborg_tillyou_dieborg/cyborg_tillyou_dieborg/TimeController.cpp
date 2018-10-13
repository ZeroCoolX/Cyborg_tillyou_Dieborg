#include "TimeController.h"

const int TimeController::PLAY_STATE = 0, TimeController::PAUSE_STATE = 1;

TimeController::TimeController():m_deltaTimeInSeconds(0), m_lastUpdate(0)
{
	m_timeState = PLAY_STATE;
}

void TimeController::update_time()
{
	if (m_timeState == PAUSE_STATE) {
		m_deltaTimeInSeconds = 0;
	}
	else {
		Uint32 timeDiff = SDL_GetTicks() - m_lastUpdate;
		m_deltaTimeInSeconds = timeDiff / 1000.0; // Move miliseconds into the decimal place area e.g. 104 = 0.104s
	}
	m_lastUpdate = SDL_GetTicks();
}

void TimeController::pause()
{
	m_timeState = PAUSE_STATE;
}

void TimeController::resume()
{
	m_timeState = PLAY_STATE;
}

void TimeController::reset()
{
	m_deltaTimeInSeconds = 0;
	m_lastUpdate = SDL_GetTicks();
}

// Builds a global TimeController object for use anywhere
TimeController TimeController::s_timeController;


