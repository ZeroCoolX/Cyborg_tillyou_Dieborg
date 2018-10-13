#include "KeyboardInput.h"

SDL_Scancode UP, DOWN, LEFT, RIGHT;
SDL_Scancode SLASH, DASH;

KeyboardInput::KeyboardInput()
	:UP(SDL_SCANCODE_UP), 
	DOWN(SDL_SCANCODE_DOWN), 
	LEFT(SDL_SCANCODE_LEFT), 
	RIGHT(SDL_SCANCODE_RIGHT),
	SLASH(SDL_SCANCODE_Z),// SDL_SCANCODE_KP_ENTER
	DASH(SDL_SCANCODE_X)// SDL_SCANCODE_KP_SPACE
{
}

// Once again - horrible, use maps.........
// TODO:  refactor after tutorial
void KeyboardInput::update(SDL_Event* e)
{
	// button press
	if (e->type == SDL_KEYDOWN) {
		if (e->key.keysym.scancode == DASH) {
			m_hero->dash();
		}
		if (e->key.keysym.scancode == SLASH) {
			m_hero->slash();
		}
	}

	// button hold
	// check for keys being held
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	// if hero not able to move or no direction buttons are held down, then stop moving
	if ((m_hero->m_state != Hero::HERO_STATE_MOVE && m_hero->m_state != Hero::HERO_STATE_IDLE)
		|| (!keyStates[UP] && !keyStates[DOWN] && !keyStates[LEFT] && !keyStates[RIGHT])){
		m_hero->m_moving = false;
	}
	else {
		// Im pretty sure he's wrong...
		if (keyStates[UP]) {
			// down right
			if (keyStates[RIGHT]) {
				m_hero->move(315); // angle
			}
			else if (keyStates[LEFT]) {
				m_hero->move(225); // angle
			}
			else {
				m_hero->move(270); // angle
			}
		}
		if (keyStates[DOWN]) {
			// up right
			if (keyStates[RIGHT]) {
				m_hero->move(45); // angle
			}
			else if (keyStates[LEFT]) {
				m_hero->move(135); // angle
			}
			else {
				m_hero->move(90); // angle
			}
		}
		// Left
		if (keyStates[LEFT] && !keyStates[UP] && !keyStates[DOWN] && !keyStates[RIGHT]) {
			m_hero->move(180);
		}
		// Right
		if (keyStates[RIGHT] && !keyStates[UP] && !keyStates[DOWN] && !keyStates[LEFT]) {
			m_hero->move(0);
		}
	}
}

