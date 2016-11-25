#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

class GameEngine
{
public:
    struct GameSettings {
        char* title;
        int width;
        int height;
    };
    struct Texture {
        SDL_Texture* texture;
        SDL_Rect dstRect;
    };
    GameEngine();
    GameEngine(GameSettings game_settings);
    ~GameEngine();
    bool init();
    bool createWindow();
    void playBackgroundMusic(std::string path);
    void playSoundEffect(std::string path);
    void renderEverything();
    void gameLoop();
    SDL_Texture* createObjectTexture(std::string path);
    SDL_Texture* createTextTexture(std::string path,
        std::string message,
        int fontSize,
        Uint8 rColor,
        Uint8 gColor,
        Uint8 bColor);
    SDL_Renderer* createRenderer(SDL_Window* window);
    SDL_Texture* loadBackgroundTexture(std::string path);
    SDL_Surface* getWindowSurface(SDL_Window* window);
    SDL_Surface* backgroundSurface;
    SDL_Texture* backgroundTexture;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* backgroundMusic;
    std::vector<Texture> toRender;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "Space Invaders";
};

