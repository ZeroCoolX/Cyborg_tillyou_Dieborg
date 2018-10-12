#include "DrawingFunctions.h"

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture *load_texture(const std::string &file, SDL_Renderer *renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr) {
		cout << "LoadTexture error" << endl;
	}
	return texture;
}

/**
*Loads an image up as a surface. Generally we want to do this if we want to palette swap
*/
SDL_Surface *load_surface(const std::string &file, SDL_Renderer *renderer)
{
	SDL_Surface *surface = IMG_Load(file.c_str());
	if (surface == nullptr) {
		cout << "LoadSurface error" << endl;
	}
	return surface;
}

/**
*Copies the palette of 1 surface to another
*/
void surface_palette_swap(SDL_Surface *surface, SDL_Surface *palette)
{
	SDL_SetPaletteColors(surface->format->palette, palette->format->palette->colors, 0, palette->format->palette->ncolors);
}

/**
*Converts a surface to a texture and optionally deletes the surface
*/
SDL_Texture *convert_surface_to_texture(SDL_Surface *surface, SDL_Renderer *renderer, bool cleanSurface)
{
	SDL_Texture	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (cleanSurface) {
		cleanup(surface);
	}
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void render_texture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect destination, SDL_Rect *clip)
{
	SDL_RenderCopy(renderer, texture, clip, &destination);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of
*	the texture's
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void render_texture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	if (clip != nullptr) {
		destination.w = clip->w;
		destination.h = clip->h;
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
	}
	render_texture(texture, renderer, destination, clip);
}

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* render_text(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	// Open the font
	TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr) {
		cout << "TTF_OpenFont error" << endl;
		return nullptr;
	}
	// We need to first render to a surface as that's what TTF_RenderText
	// returns, then load surface into a texture
	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr) {
		cout << "TTD_RenderText error" << endl;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		cout << "CraeteTexture error" << endl;
	}
	// Cleanup the surface and font
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* render_text(const std::string &message, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
	if (font == nullptr) {
		cout << "TTF_OpenFont" << endl;
		return nullptr;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr) {
		cout << "TTF_RenderText" << endl;
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		cout << "CreateTexture" << endl;
	}
	//Clean up the surface and font
	SDL_FreeSurface(surface);
	return texture;
}

bool save_screenshot_BMP(std::string filepath, SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;
	infoSurface = SDL_GetWindowSurface(window);
	if (infoSurface == NULL) {
		std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n" << endl;
	}
	else {
		unsigned char* pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == 0) {
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n" << endl;
			return false;
		}
		else {
			if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				std::cerr << "Failed to read pixel fata from renderer object. SDL_GetError() -" << SDL_GetError() << "\n" <<endl;
				pixels = NULL;
				return false;
			}
			else {
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
				if (saveSurface == NULL) {
					std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n" << endl;
					return false;
				}
				SDL_SaveBMP(saveSurface, filepath.c_str());
				SDL_FreeSurface(saveSurface);
				saveSurface = NULL;
			}
			delete[] pixels;
		}
		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}
	return true;
}
