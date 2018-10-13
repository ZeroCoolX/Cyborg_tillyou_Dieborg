#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include "Animation.h"

using namespace std;

// Each "player" you want to animatw will have an AnimationSet
class AnimationSet {
public:
	string m_imageName;
	SDL_Texture* m_spriteSheet;
	SDL_Texture* m_whiteSpriteSheet = NULL; // Damage sprite sheet (flashes white)
	list<Animation> m_animations;

	~AnimationSet(); // Cleans up resources (dynamic memory e.g. textures)

	Animation* get_animation(string name);
	void load_animation_set(string fileName, list<DataGroupType>& groupTypes, bool setColorKey = false, int transparentPixelIndex = 0, bool createWhiteTexture = false);
};

#endif // !ANIMATIONSET_H
