#include "GameEngine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>


#define FPS 60

namespace Engine {

    GameEngine::GameSettings engineSettings;

    GameEngine::GameEngine() {
        window = nullptr;
        backgroundSurface = nullptr;
        backgroundTexture = nullptr;
        renderer = nullptr;
        backgroundMusic = nullptr;
    }
    GameEngine::GameEngine(GameSettings game_settings)
    {
        window = nullptr;
        backgroundSurface = nullptr;
        backgroundTexture = nullptr;
        renderer = nullptr;
        backgroundMusic = nullptr;
        engineSettings = game_settings;
    }

    bool GameEngine::createWindow()
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

        if (!createWindow())
            return false;

        if (IMG_Init(IMG_INIT_PNG) == 0) {
            printf("Unable to initialize SDL_image: %s\n", IMG_GetError());
            return false;
        }

        if (TTF_Init() == -1) {
            printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
            return false;
        }

        if (Mix_Init(MIX_INIT_OGG) == 0) {
            printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
            return false;
        }

        if (backgroundSurface == nullptr)
            backgroundSurface = SDL_GetWindowSurface(window);

        if (renderer == nullptr)
            renderer = createRenderer(window);

        return true;
    }

    void GameEngine::gameLoop() {
        bool quit = false;

        while (!quit) {
            Uint32 nextTick = SDL_GetTicks() + FPS;
            SDL_Event event;
            size_t numberOfProjectiles = projectiles.size();

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_LCTRL:
                    case SDLK_RCTRL:
                        if (numberOfProjectiles < 10)
                            fireProjectile();
                        break;
                    case SDLK_y:
                        if (!gameStarted) {
                            startNewGame();
                            gameStarted = true;
                        }
                        break;
                    case SDLK_F8: toggleMusic(); break;
					default:
						player->react(event);
						for (auto sprite : gameSprites)
						{
							sprite->react(event);
						}
                    }
                }
            }

            int delay = nextTick - SDL_GetTicks();
            if (delay > 0)
                SDL_Delay(delay);
            moveMovables();
            renderEverything();
        }
    }

    void GameEngine::moveEnemiesDown() {
        for (auto i = 0; i < numberOfEnemies; i++) {
            auto search = gameObjects.find("enemy" + std::to_string(i));
            search->second->incrementRectY(5);

        }
    }

    void GameEngine::moveMovables() {
        if (gameStarted) {
            for (auto i = 0; i < numberOfEnemies; i++) {
                std::string enemyName = "enemy" + std::to_string(i);
                auto search = gameObjects.find(enemyName);
                if (search != gameObjects.end()) {
                    if (enemyName == "enemy10" && search->second->getRect().x > 740) {
                        moveEnemiesDown();
                        movementDirection = -1;
                    }
                    if (enemyName == "enemy0" && search->second->getRect().x < 0) {
                        moveEnemiesDown();
                        movementDirection = 1;
                    }
                    search->second->incrementRectX(movementDirection);
                }
            }
            moveOrDestroyProjectile(projectiles);
        }
    }

    void GameEngine::moveOrDestroyProjectile(std::vector<Sprite*>) {
        for (auto i = 0; i < projectiles.size(); i++) {
            auto projectile = projectiles.at(i);
            projectile->setRectY(projectile->getRect().y - PROJECTILE_VELOCITY);
            if (projectile->getRect().y < 0) {
                delete projectile;
                projectiles.erase(projectiles.begin() + i);
                break;
            }
            for (auto j = 0; j < numberOfEnemies; j++) {
                std::string enemyName = "enemy" + std::to_string(j);
                auto search = gameObjects.find(enemyName);
                if (SDL_HasIntersection(&projectile->getRect(), &search->second->getRect()) && search->second->isDrawn()) {
                    delete projectile;
                    projectiles.erase(projectiles.begin() + i);
                    search->second->setDrawn(false);
                    break;
                }
            }
        }
    }

    void GameEngine::startNewGame() {
        gameObjects.erase("PRESS 'Y' TO START A NEW GAME");
		createPlayer();
        int enemyX = 25; int enemyY = 5;
        std::string enemyName = "enemy";
        for (auto i = 0; i < numberOfEnemies; i++) {
            enemyName = "enemy" + std::to_string(i);
            createObjectTexture("res/enemy.png", enemyName, enemyX, enemyY, true);
            enemyX += 70;
            if (i != 0 && i % 10 == 0) {
                enemyX = 25;
                enemyY += 70;
            }
        }
    }
	void GameEngine::createPlayer()
    {		
		player = new Player(createSprite(playerPath, "player", playerX, playerY, true));
		gameSprites.push_back(player);
    } 
    void GameEngine::toggleMusic() {
        if (musicPlaying)
        {
            volume = Mix_VolumeMusic(-1);
            Mix_VolumeMusic(0); //set volume to 0 for all channels (-1)
            musicPlaying = false;
        }
        else {
            Mix_VolumeMusic(volume); //restore original volume
            musicPlaying = true;
        }
    }

    void GameEngine::playBackgroundMusic(std::string path) {
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096))
            printf("Error loading audio: %s\n", Mix_GetError());

        backgroundMusic = Mix_LoadMUS(path.c_str());

        if (!backgroundMusic)
            printf("Error playing audio: %s\n", Mix_GetError());

        Mix_PlayMusic(backgroundMusic, -1);
        musicPlaying = true;
    }

    void GameEngine::renderEverything() {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        for (std::pair<std::string, Sprite*> var : gameObjects) {
            if (var.second->isDrawn())
                SDL_RenderCopy(renderer, var.second->getTexture(), NULL, &var.second->getRect());
        }
		for (auto var : gameSprites)
		{
			SDL_RenderCopy(renderer, var->getTexture(), NULL, &var->getRect());
		}
        for (Sprite* var : projectiles) {
            SDL_RenderCopy(renderer, var->getTexture(), NULL, &var->getRect());
        }

        SDL_RenderPresent(renderer);
    }



    void GameEngine::fireProjectile() {
		//TODO: move to the player class
        SDL_Surface* surface = IMG_Load("res/projectile.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int projectileWidth = surface->w, projectileHeight = surface->h;
        SDL_Rect projectileRectangle = { player->getRect().x + 30, player->getRect().y + 10, projectileWidth, projectileHeight };
        SDL_FreeSurface(surface);
        Sprite* projectileTexture = new Sprite(texture, projectileRectangle, true);
        projectiles.emplace_back(projectileTexture);
    }

    void GameEngine::createObjectTexture(std::string path, std::string name, int initialPosX, int initialPosY, bool drawn)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int textureWidth = surface->w, textureHeight = surface->h;
        SDL_Rect textureRectangle = { initialPosX, initialPosY, textureWidth, textureHeight };
        SDL_FreeSurface(surface);
        Sprite* myTexture = new Sprite(texture, textureRectangle, drawn);
        gameObjects.insert({ name, myTexture });
    }

	Sprite* GameEngine::createSprite(std::string path, std::string name, int initialPosX, int initialPosY, bool drawn)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		int textureWidth = surface->w, textureHeight = surface->h;
		SDL_Rect textureRectangle = { initialPosX, initialPosY, textureWidth, textureHeight };
		SDL_FreeSurface(surface);
		Sprite* myTexture = new Sprite(texture, textureRectangle, drawn);
		return myTexture;
	}
    void GameEngine::createTextTexture(std::string path, std::string message,
        int fontSize, Uint8 rColor, Uint8 gColor, Uint8 bColor) {

        TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
        SDL_Color color = { rColor, gColor, bColor };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textWidth = textSurface->w, textHeight = textSurface->h;
        SDL_Rect textRectangle = { 100, 250, textWidth, textHeight };

        SDL_FreeSurface(textSurface);
        Sprite* txt = new Sprite(textTexture, textRectangle, true);
        gameObjects.insert({ message, txt });
    }

    SDL_Texture* GameEngine::loadBackgroundTexture(std::string path) {
        SDL_Surface* adjustedSurface = nullptr;
        SDL_Surface* initialSurface = IMG_Load(path.c_str());

        if (initialSurface == nullptr) {
            printf("Unable to load image %s: %s\n", path.c_str(), IMG_GetError());
            return nullptr;
        }

        adjustedSurface = SDL_ConvertSurface(initialSurface, backgroundSurface->format, 0);
        if (adjustedSurface == nullptr) {
            printf("Unable to adjust image %s: %s\n", path.c_str(), SDL_GetError());
        }

        SDL_FreeSurface(initialSurface);
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, adjustedSurface);
        SDL_FreeSurface(adjustedSurface);
        return backgroundTexture;
    }

    SDL_Surface* GameEngine::getWindowSurface(SDL_Window* window) {
        return window != nullptr ? SDL_GetWindowSurface(window) : nullptr;
    }

    void GameEngine::setTexture(std::string path) {
        backgroundTexture = loadBackgroundTexture(path);
    }

    void GameEngine::setPlayerPath(std::string path) {
        playerPath = path;
    }

    SDL_Renderer* GameEngine::createRenderer(SDL_Window* window) {
        return SDL_CreateRenderer(window, -1, 0);
    }

    GameEngine::~GameEngine() {
        for (std::pair<std::string, Sprite*> var : gameObjects) {
            delete var.second;
        }
        gameObjects.clear();
        projectiles.clear();
        Mix_FreeMusic(backgroundMusic);
        Mix_CloseAudio();
        SDL_FreeSurface(backgroundSurface);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    GameEngine gameEngine;

}