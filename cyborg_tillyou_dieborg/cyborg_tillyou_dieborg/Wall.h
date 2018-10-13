#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity {
public:
	const string WALL_ANIMATION_NAME = "wall";

	Wall(AnimationSet* animSet);
	void update();
	void change_animation(int newState, bool resetFrameToStart);
	void update_collisions() {
		// Purposely do nothing.
		// Walls don't move or get pushed
	}
};

#endif // !WALL_H
