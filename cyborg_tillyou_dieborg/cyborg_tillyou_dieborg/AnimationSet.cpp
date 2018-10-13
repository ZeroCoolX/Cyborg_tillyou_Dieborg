#include "AnimationSet.h"


AnimationSet::~AnimationSet()
{
	cleanup(spriteSheet);
	if (whiteSpriteSheet != NULL) {
		cleanup(whiteSpriteSheet);
	}
}

Animation* AnimationSet::get_animation(string name)
{
	list<Animation>::iterator animIterator = animations.begin();
	while (animIterator != animations.end()) {
		if ((*animIterator).name == name) {
			return &(*animIterator);
		}
		++animIterator;
	}
	return NULL;
}
