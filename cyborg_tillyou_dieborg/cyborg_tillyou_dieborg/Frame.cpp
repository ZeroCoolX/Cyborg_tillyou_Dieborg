#include "Frame.h"

void Frame::draw(SDL_Texture* spriteSheet, float x, float y)
{
	SDL_Rect destination; // Where we want to draw this frame
	// set position
	destination.x = x - offset.x;
	destination.y = y - offset.y;
	// set dimensions
	destination.w = clip.w;
	destination.h = clip.h;

	render_texture(spriteSheet, Globals::renderer, destination, &clip);
}
