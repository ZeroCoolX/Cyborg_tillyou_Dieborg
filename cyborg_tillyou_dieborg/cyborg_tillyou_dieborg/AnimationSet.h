#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include "Animation.h"

using namespace std;

// Each "player" you want to animatw will have an AnimationSet
class AnimationSet {
public:
	string imageName;
	SDL_Texture* spriteSheet;
	SDL_Texture* whiteSpriteSheet = NULL; // Damage sprite sheet (flashes white)
	list<Animation> animations;

	~AnimationSet(); // Cleans up resources (dynamic memory e.g. textures)

	Animation* get_animation(string name);
	// TODO load_animation_set
};

#endif // !ANIMATIONSET_H
