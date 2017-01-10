#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "SmartPointers.h"

namespace Engine {

	struct GameSettings {
		char* title;
		int width;
		int height;
		int fps;
	};
    class GameEngine
    {
    public:
		static void configure(GameSettings settings);
        GameEngine();
        GameEngine(GameSettings game_settings);
	    ~GameEngine();
        bool init();
        void setPlayerPath(std::string path);
        void playBackgroundMusic(std::string path);
	    void render();
	    void gameLoop();
		bool hasCollision(Sprite& sprite);
		bool hasProjectileCollision(Sprite & sprite);
        void setNumberOfEnemies(int newNumber) { numberOfEnemies = newNumber; }
		Sprite * createSprite(std::string path, std::string name, int initialPosX, int initialPosY, bool drawn = true);
		void createProjectile(std::string path, SpaceGame::Player&);
		void createTextTexture(std::string path,
            std::string message,
            int fontSize,
            Uint8 rColor,
            Uint8 gColor,
            Uint8 bColor);
        SDL_Texture* loadBackgroundTexture(std::string path);
        int getScreenWidth() { return SCREEN_WIDTH; }
		TextureShPtr createTexture(std::string path);
	    GraphicShPtr createGraphic(std::string path);
	    void addSprite(Sprite* sprite);
    protected:
    private:
		int FPS;
	    SpaceGame::Player* player;
        bool createWindow();
        //void createObjectTexture(std::string path, std::string name, int initialPosX, int initialPosY, bool drawn = true);
        void setTexture(std::string path);
		SDL_Texture* newTexture(SDL_Surface*);
        void renderEverything();
		void startNewGame();
		void createPlayer();
		void toggleMusic();
		bool musicPlaying;
		int volume;
        void moveMovables();
        void fireProjectile();
        void moveOrDestroyProjectile(std::vector<Sprite*> projectiles);
        int getNumberOfEnemies() const { return numberOfEnemies; }
        int playerX = 368;
		int playerY = 500;
        int numberOfEnemies;
        int movementDirection = 1;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
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
		std::vector<Sprite*> sprites;
        std::vector<Sprite*> projectiles;
		std::vector<SpaceGame::Enemy*> gameSprites;
        std::unordered_map<std::string, Sprite*> gameObjects;
        std::string playerPath;
        bool gameStarted = false;
    };
}
#endif
