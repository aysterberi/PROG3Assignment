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
            bool movable;
            bool isDrawn;
        };
        GameEngine();
        GameEngine(GameSettings game_settings);
        ~GameEngine();
        bool init();
        bool createWindow();
        void startNewGame();
        void playBackgroundMusic(std::string path);
        void renderEverything();
        void gameLoop();
        void setTexture(std::string path);
        void setPlayerPath(std::string path);
        void createObjectTexture(std::string path,
            std::string name,
            int initialPosX,
            int initialPosY,
            bool movable = false,
            bool isDrawn = true);
        void createTextTexture(std::string path,
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
        int getNumberOfEnemies() const { return numberOfEnemies; }
        void setNumberOfEnemies(int newNumber) { numberOfEnemies = newNumber; }
    protected:
    private:
        void moveLeft();
        void moveRight();
        void moveMovables();
        void moveEnemiesDown();
        void fireProjectile();
        void moveOrDestroyProjectile(std::vector<Texture> projectiles);
        int getPlayerX();
        int getPlayerY();
        std::unordered_map<std::string, Texture> gameObjects;
        std::vector<Texture> projectiles;
        SDL_Surface* backgroundSurface;
        SDL_Texture* backgroundTexture;
        SDL_Window* window;
        SDL_Renderer* renderer;
        Mix_Music* backgroundMusic;
        std::string playerPath;
        bool gameStarted = false;
        static const int PROJECTILE_VELOCITY = 5;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const char* WINDOW_TITLE = "Space Invaders";
        const int playerY = 500;
        int playerX = 368;
        int numberOfEnemies;
        int movementDirection = 1;
        SDL_Rect playerRect;
        SDL_Surface* playerSurface;
        SDL_Texture* playerTexture;
    };

    extern GameEngine gameEngine;
}
#endif
