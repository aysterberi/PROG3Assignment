#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

class GameEngine
{
public:
	struct GameSettings
	{
		char *title;
		int width;
		int height;
	};
    GameEngine();
	GameEngine(GameSettings game_settings);
	bool CreateWindow();
	~GameEngine();
    bool init();
    SDL_Surface* loadSurface(std::string path);
    SDL_Surface* surface;
    SDL_Window* window;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "Space Invaders";
};

