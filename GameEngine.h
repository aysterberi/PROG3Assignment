#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <unordered_map>
namespace Engine {
    class GameEngine
    {
    public:
        struct GameSettings {
            char* title;
            int width;
            int height;
        };
        GameEngine();
        GameEngine(GameSettings game_settings);
        ~GameEngine();
        bool init();
        void setPlayerPath(std::string path);
        void playBackgroundMusic(std::string path);
        void gameLoop();
        void setNumberOfEnemies(int newNumber) { numberOfEnemies = newNumber; }
        void createTextTexture(std::string path,
            std::string message,
            int fontSize,
            Uint8 rColor,
            Uint8 gColor,
            Uint8 bColor);
        SDL_Texture* loadBackgroundTexture(std::string path);
    protected:
    private:
        bool createWindow();
        void createObjectTexture(std::string path,
            std::string name,
            int initialPosX,
            int initialPosY,
            bool isDrawn = true);
        void setTexture(std::string path);
        void renderEverything();
        void startNewGame();
		void toggleMusic();
		bool musicPlaying;
		int volume;
        void moveLeft();
        void moveRight();
        void moveMovables();
        void moveEnemiesDown();
        void fireProjectile();
        void moveOrDestroyProjectile(std::vector<Sprite*> projectiles);
        int getNumberOfEnemies() const { return numberOfEnemies; }
        int getPlayerX();
        int getPlayerY();
        int playerX = 368;
        int numberOfEnemies;
        int movementDirection = 1;
        const int PROJECTILE_VELOCITY = 5;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const int PLAYER_Y = 500;
        const char* WINDOW_TITLE = "Space Invaders";
        SDL_Window* window;
        SDL_Surface* backgroundSurface;
        SDL_Surface* getWindowSurface(SDL_Window* window);
        SDL_Texture* getTexture() const { return backgroundTexture; }
        SDL_Texture* backgroundTexture;
        SDL_Renderer* getRenderer() const { return renderer; }
        SDL_Renderer* createRenderer(SDL_Window* window);
        SDL_Renderer* renderer;
        Mix_Music* backgroundMusic;
        std::vector<Sprite*> projectiles;
        std::unordered_map<std::string, Sprite*> gameObjects;
        std::string playerPath;
        bool gameStarted = false;
    };

    extern GameEngine gameEngine;
}
#endif
