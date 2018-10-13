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

void AnimationSet::load_animation_set(string fileName, list<DataGroupType>& groupTypes, bool setColorKey, int transparentPixelIndex, bool createWhiteTexture)
{
	ifstream file;
	string resPath = get_resource_path();
	file.open(resPath + fileName);
	if (file.good()) {
		getline(file, imageName);
		if (setColorKey) {
			SDL_Surface* spriteSurface = load_surface(resPath + imageName, Globals::renderer);

			// For transparency we will grab the [transparentPixelIndex] from the surface we just made
			SDL_Color* transparentPixel = &spriteSurface->format->palette->colors[transparentPixelIndex];
			SDL_SetColorKey(spriteSurface, 1, SDL_MapRGB(spriteSurface->format, transparentPixel->r, transparentPixel->g, transparentPixel->b));

			spriteSheet = convert_surface_to_texture(spriteSurface, Globals::renderer, false);

			if (createWhiteTexture) {
				SDL_Surface* whiteSurface = load_surface(resPath + "allwhite.png", Globals::renderer);
				surface_palette_swap(spriteSurface, whiteSurface);
				SDL_SetColorKey(spriteSurface, 1, SDL_MapRGB(spriteSurface->format, transparentPixel->a, transparentPixel->g, transparentPixel->b));
				whiteSpriteSheet = convert_surface_to_texture(spriteSurface, Globals::renderer, false);
				
				cleanup(whiteSurface);
			}
			else {
				whiteSpriteSheet = NULL;
			}
			cleanup(spriteSurface);
		}
		else {
			spriteSheet = load_texture(resPath + imageName, Globals::renderer);
		}

		string buffer;
		getline(file, buffer);
		stringstream ss;
		buffer = Globals::clip_off_data_header(buffer);
		ss << buffer;
		int numberOfAnimations;
		ss >> numberOfAnimations;

		for (int i = 0; i < numberOfAnimations; ++i) {
			Animation newAnimation;
			newAnimation.load_animation(file, groupTypes);
			animations.push_back(newAnimation);
		}
	}
	file.close();
}
