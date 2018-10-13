#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "Hero.h"

class KeyboardInput{
public:
	Hero* m_hero;
	SDL_Scancode UP, DOWN, LEFT, RIGHT;
	SDL_Scancode SLASH, DASH;

	KeyboardInput();
	void update(SDL_Event* e);
};

#endif // !KEYBOARDINPUT_H
