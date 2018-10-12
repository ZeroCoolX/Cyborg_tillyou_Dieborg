#ifndef DRAWINGFUNCS_H
#define DRAWINGFUNCS_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "ResPath.h"
#include "Cleanup.h"

using namespace std;

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param renderer The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* load_texture(const std::string &file, SDL_Renderer* renderer);

/**
* Loads an image up as a surface. Generally we want to do this is we want to palette swap
*/
SDL_Surface* load_surface(const std::string &file, SDL_Renderer* renderer);

/**
* Copies the palette of 1 surface to another
*/
void surface_palette_swap(SDL_Surface* surface, SDL_Surface* palette);

/**
*Converts a surface to a texture and optionally deletes the surface
*/
SDL_Texture* convert_surface_to_texture(SDL_Surface* surface, SDL_Renderer* renderer, bool cleanSurface = false);

/**
* Draws an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect destination, SDL_Rect* clip = nullptr);

/**
* Draw an SDL_Tecture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired.
* If a clip is passed, the clip's width and height will be used instead of
*	the texture's
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* render_text(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* render_text(const std::string &message, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);

bool save_screenshot_BMP(std::string filepath, SDL_Window* window, SDL_Renderer* renderer);

#endif


