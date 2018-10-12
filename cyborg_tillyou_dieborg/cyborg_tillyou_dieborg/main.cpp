#include "cleanup.h"
#include "res_path.h"
#include "drawing_functions.h"
#include<SDL_mixer.h>

int main(int argc, char **argv) {
	// Setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error initializing SDL" << endl;
		return 1;
	}

	// Setup window
	SDL_Window *window = SDL_CreateWindow("Cybordg Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 352, SDL_WINDOW_SHOWN); // SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
	if (window == nullptr) {
		SDL_Quit();
		cout << "Window error" << endl;
		return 1;
	}

	// Setup renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cleanup(window);
		SDL_Quit();
		cout << "Renderer error" << endl;
		return 1;
	}

	// This is the size to draw things at, before we scale it to the screen size dimentions mentioned in createWindow
	// Useful for pixel art
	// For example: 2X pixels is half of the windows Height and Width
	SDL_RenderSetLogicalSize(renderer, 640, 352);

	// Initialize sdl_image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_Quit();
		cout << "sdl_image did not initialize" << endl;
		return 1;
	}

	// Setup text to font
	if (TTF_Init() != 0) {
		SDL_Quit();
		cout << "sdl_ttf did not initialize" << endl;
		return 1;
	}

	// Setup the sdl_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_Quit();
		cout << "sdl_mixer did not initialize" << endl;
		return 1;
	}

	// Load up a texture to draw
	string resPath = getResourcePath();
	SDL_Texture *texture = loadTexture(resPath + "map.png", renderer);

	// Run game for 5000 ticks (5000ms)
	while (SDL_GetTicks() < 5000) {
		// Clear the screen
		SDL_RenderClear(renderer);
		// Draw what we want to the screen
		renderTexture(texture, renderer, 0, 0);
		// Show image we rendered
		SDL_RenderPresent(renderer);
	}

	cleanup(texture);
	cleanup(renderer);
	cleanup(window);
	
	SDL_Quit();
	return 0;
}
