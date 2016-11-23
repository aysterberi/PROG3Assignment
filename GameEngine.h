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
		char* title;
		int width;
		int height;
	};
    GameEngine();
	GameEngine(GameSettings game_settings);
    ~GameEngine();
    bool init();
    bool createWindow();
    void playBackgroundMusic(std::string path);
    void renderEverything();
    void gameLoop();
    SDL_Texture* createText(std::string path,
                    std::string message,
                    int fontSize,
                    int rColor,
                    int gColor,
                    int bColor);
    SDL_Renderer* createRenderer(SDL_Window* window);
    SDL_Texture* loadTexture(std::string path);
    SDL_Surface* getWindowSurface(SDL_Window* window);
    SDL_Surface* backgroundSurface;
    SDL_Texture* backgroundTexture;
    SDL_Texture* textTexture;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect textRectangle;
    Mix_Chunk* backgroundMusic;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "Space Invaders";
};

