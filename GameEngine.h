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
        GameEngine();
        GameEngine(GameSettings game_settings);
	    ~GameEngine();

		void setBackground(std::string path);
        void setBackgroundMusic(std::string path);

		GraphicShPtr createTextGraphic(TTF_Font * font, std::string text, SDL_Color color);
		GraphicShPtr createGraphic(std::string path);

		void addSprite(Sprite* sprite);
		void addProjectile(Sprite* projectile);
		void addMessage(Sprite* sprite, int duration);
		void removeGameObject(std::string key);

		bool init();
	    void gameLoop();
		void stop();

		bool hasCollision(Sprite& sprite);
	    bool hasProjectileCollision(Sprite & sprite);

		int getScreenWidth() { return SCREEN_WIDTH; }
		int getSreenHeight() { return SCREEN_HEIGHT; }
    protected:
    private:
		int FPS;
	    SpaceGame::Player* player;
        bool createWindow();
		SDL_Texture* newTexture(SDL_Surface*);
        void renderEverything();
		void toggleMusic();
		bool musicPlaying;
		int volume;
		void moveMovables();
        void moveOrDestroyProjectile(std::vector<Sprite*> projectiles);
		bool gameStarted = false;
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const char* WINDOW_TITLE = "Space Invaders";
        SDL_Window* window;
        SDL_Surface* backgroundSurface;
        SDL_Texture* getTexture() const { return backgroundTexture; }
        SDL_Texture* backgroundTexture;
        SDL_Renderer* getRenderer() const { return renderer; }
        SDL_Renderer* createRenderer(SDL_Window* window);
        SDL_Renderer* renderer;
        Mix_Music* backgroundMusic;
		std::vector<Sprite*> sprites;
        std::vector<Sprite*> projectiles;
		std::vector<Sprite*> messages;
		std::vector<SpaceGame::Enemy*> gameSprites;
        std::unordered_map<std::string, Sprite*> gameObjects;

    };
}
#endif
