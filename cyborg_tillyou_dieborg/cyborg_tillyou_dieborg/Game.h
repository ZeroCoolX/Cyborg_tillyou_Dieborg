#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "Hero.h"
#include "Wall.h"
#include "KeyboardInput.h"
#include "DrawingFunctions.h"

class Game {
public:
	const int WALL_SPRITE_SIZE = 32;

	AnimationSet* m_heroAnimSet;
	AnimationSet* m_wallAnimSet;

	SDL_Texture* m_backgroundImage;

	Hero* m_hero;
	KeyboardInput m_heroInput;

	list<Entity*> m_walls;

	Game();
	~Game();

	void update();
	void draw();
};


#endif // !GAME_H
