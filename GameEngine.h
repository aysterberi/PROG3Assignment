#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "GameObject.h"
namespace Engine {
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
        void startNewGame();
        void playBackgroundMusic(std::string path);
        void playSoundEffect(std::string path);
        void renderEverything();
        void gameLoop();
        void setTexture(std::string path);
        void setPlayerPath(std::string path);
        void createObjectTexture(std::string path, std::string name, int, int);
        SDL_Texture* createTextTexture(std::string path,
            std::string message,
            int fontSize,
            Uint8 rColor,
            Uint8 gColor,
            Uint8 bColor);
        SDL_Renderer* createRenderer(SDL_Window* window);
        SDL_Renderer* getRenderer() const { return renderer; }
        SDL_Texture* loadBackgroundTexture(std::string path);
        SDL_Surface* getWindowSurface(SDL_Window* window);
        SDL_Texture* getTexture() const { return backgroundTexture; }
    protected:
    private:
        std::unordered_map<std::string, Texture> gameObjects;
        std::vector<Texture> toRender;
        SDL_Surface* backgroundSurface;
        SDL_Texture* backgroundTexture;
        SDL_Window* window;
        SDL_Renderer* renderer;
        Mix_Music* backgroundMusic;
        std::string playerPath;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const char* WINDOW_TITLE = "Space Invaders";
        SDL_Surface* playerSurface;
        SDL_Texture* playerTexture;
    };

    extern GameEngine gameEngine;
}
#endif
