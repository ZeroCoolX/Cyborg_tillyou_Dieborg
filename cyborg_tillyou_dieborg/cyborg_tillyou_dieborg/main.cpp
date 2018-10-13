#include "cleanup.h"
#include "ResPath.h"
#include "DrawingFunctions.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Game.h"

int main(int argc, char** argv) {
	// Setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error initializing SDL" << endl;
		return 1;
	}

	// Setup window
	SDL_Window* window = SDL_CreateWindow("Cybordg Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Globals::screenWidth*Globals::screenScale, Globals::screenHeight*Globals::screenScale, SDL_WINDOW_SHOWN); // SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
	if (window == nullptr) {
		SDL_Quit();
		cout << "Window error" << endl;
		return 1;
	}

	// Setup renderer
	Globals::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Globals::renderer == nullptr) {
		cleanup(window);
		SDL_Quit();
		cout << "Renderer error" << endl;
		return 1;
	}

	// This is the size to draw things at, before we scale it to the screen size dimentions mentioned in createWindow
	// Useful for pixel art
	// For example: 2X pixels is half of the windows Height and Width
	SDL_RenderSetLogicalSize(Globals::renderer, Globals::screenWidth, Globals::screenHeight);

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
	//string resPath = get_resource_path();
	//SDL_Texture* texture = load_texture(resPath + "map.png", Globals::renderer);

	//// Run game for 5000 ticks (5000ms)
	//while (SDL_GetTicks() < 5000) {
	//	// Clear the screen
	//	SDL_RenderClear(Globals::renderer);
	//	// Draw what we want to the screen
	//	render_texture(texture, Globals::renderer, 0, 0);
	//	// Show image we rendered
	//	SDL_RenderPresent(Globals::renderer);
	//}

	Game game;
	game.update();

	//cleanup(texture);
	cleanup(Globals::renderer);
	cleanup(window);
	
	SDL_Quit();
	return 0;
}
