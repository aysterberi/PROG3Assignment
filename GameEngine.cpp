#include "GameEngine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

GameEngine::GameSettings engineSettings;

GameEngine::GameEngine() {
    window = nullptr;
    surface = nullptr;
}
GameEngine::GameEngine(GameSettings game_settings)
{
	window = nullptr;
	surface = nullptr;
	engineSettings = game_settings;
}

bool GameEngine::CreateWindow()
{
	window = SDL_CreateWindow(engineSettings.title, 100, 100, engineSettings.width, engineSettings.height, 0);
	if (window == nullptr) {
		printf("Unable to create window: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool GameEngine::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Unable  to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

	if (CreateWindow() == false)
	{
		return false;
	}

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Unable to initialize SDL_image: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    }

    if (Mix_Init(MIX_INIT_OGG) == 0) {
        printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
    }

    surface = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface* GameEngine::loadSurface(std::string path) {
    SDL_Surface* adjustedSurface = nullptr;
    SDL_Surface* initialSurface = IMG_Load(path.c_str());

    if (initialSurface == nullptr) {
        printf("Unable to load image %s: %s\n", path.c_str(), IMG_GetError());
        return nullptr;
    }

    adjustedSurface = SDL_ConvertSurface(initialSurface, surface->format, 0);
    if (adjustedSurface == nullptr) {
        printf("Unable to adjust image %s: %s\n", path.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(initialSurface);
    return adjustedSurface;
}


GameEngine::~GameEngine() {
    SDL_DestroyWindow(window);
    window = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
