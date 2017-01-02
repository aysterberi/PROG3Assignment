#include "GameEngine.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

#define FPS 60

namespace Engine {

    // forward declarations
    // faster than using an include
    void toggleMusic();
    bool musicPlaying;
    int volume;

    GameEngine::GameSettings engineSettings;

    GameEngine::GameEngine() {
        window = nullptr;
        backgroundSurface = nullptr;
        backgroundTexture = nullptr;
        renderer = nullptr;
        backgroundMusic = nullptr;
        playerSurface = nullptr;
    }
    GameEngine::GameEngine(GameSettings game_settings)
    {
        window = nullptr;
        backgroundSurface = nullptr;
        backgroundTexture = nullptr;
        renderer = nullptr;
        backgroundMusic = nullptr;
        playerSurface = nullptr;
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

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_LCTRL:
                    case SDLK_RCTRL: fireProjectile(); break;
                    case SDLK_y:
                        if (!gameStarted) {
                            startNewGame();
                            gameStarted = true;
                        }
                        break;
                    case SDLK_a:
                    case SDLK_LEFT: moveLeft(); break;
                    case SDLK_d:
                    case SDLK_RIGHT: moveRight(); break;
                    case SDLK_F8: toggleMusic(); break;
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

    void GameEngine::moveLeft() {
        auto search = gameObjects.find("player");
        search->second.dstRect.x -= 5;
    }

    void GameEngine::moveRight() {
        auto search = gameObjects.find("player");
        search->second.dstRect.x += 5;
    }

    void GameEngine::moveEnemiesDown() {
        for (auto i = 0; i < numberOfEnemies; i++) {
            auto search = gameObjects.find("enemy" + std::to_string(i));
            search->second.dstRect.y += 5;
        }
    }

    void GameEngine::moveMovables() {
        if (gameStarted) {
            for (auto i = 0; i < numberOfEnemies; i++) {
                std::string enemyName = "enemy" + std::to_string(i);
                auto search = gameObjects.find(enemyName);
                if (search != gameObjects.end()) {
                    if (enemyName == "enemy10" && search->second.dstRect.x > 740) {
                        moveEnemiesDown();
                        movementDirection = -1;
                    }
                    if (enemyName == "enemy0" && search->second.dstRect.x < 0) {
                        moveEnemiesDown();
                        movementDirection = 1;
                    }
                    search->second.dstRect.x += movementDirection;
                }
            }
            moveOrDestroyProjectile(projectiles);
        }
    }

    void GameEngine::moveOrDestroyProjectile(std::vector<GameEngine::Texture>) {
        for (auto i = 0; i < projectiles.size(); i++) {
            auto &projectile = projectiles.at(i);
            projectile.dstRect.y -= PROJECTILE_VELOCITY;
            if (projectile.dstRect.y < 0) {
                projectiles.erase(projectiles.begin() + i);
            }
            for (auto j = 0; j < numberOfEnemies; j++) {
                std::string enemyName = "enemy" + std::to_string(j);
                auto search = gameObjects.find(enemyName);
                if (SDL_HasIntersection(&projectile.dstRect, &search->second.dstRect) && search->second.isDrawn) {
                    projectiles.erase(projectiles.begin() + i);
                    search->second.isDrawn = false;
                    break;
                }
            }
        }
    }

    void GameEngine::startNewGame() {
        gameObjects.erase("PRESS 'Y' TO START A NEW GAME");
        createObjectTexture("res/ship.png", "player", playerX, playerY, true, true);
        int enemyX = 25; int enemyY = 5;
        std::string enemyName = "enemy";
        for (auto i = 0; i < numberOfEnemies; i++) {
            enemyName = "enemy" + std::to_string(i);
            createObjectTexture("res/enemy.png", enemyName, enemyX, enemyY, true, true);
            enemyX += 70;
            if (i != 0 && i % 10 == 0) {
                enemyX = 25;
                enemyY += 70;
            }
        }
    }

    void toggleMusic() {
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

    void GameEngine::playSoundEffect(std::string path) {
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 1, 4096))
            printf("Error loading audio: %s\n", Mix_GetError());
        Mix_Chunk* shotSound = Mix_LoadWAV(path.c_str());
        if (!shotSound)
            printf("Error playing audio: %s\n", Mix_GetError());

        Mix_PlayChannel(-1, shotSound, 0);
        //Mix_FreeChunk(shotSound);
        // TODO: freeing the chunk right after we try to play it seems 
        // to not work since no sound is played, investigate docs to figure out why
        // this cannot stand, will cause memory leaks over time.
    }

    void GameEngine::renderEverything() {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        for (std::pair<std::string, Texture> var : gameObjects) {
            if (var.second.isDrawn)
                SDL_RenderCopy(renderer, var.second.texture, NULL, &var.second.dstRect);
        }
        for (Texture var : projectiles) {
            SDL_RenderCopy(renderer, var.texture, NULL, &var.dstRect);
        }

        SDL_RenderPresent(renderer);
    }

    int GameEngine::getPlayerX() {
        return gameObjects.find("player")->second.dstRect.x;
    }
    int GameEngine::getPlayerY() {
        return gameObjects.find("player")->second.dstRect.y;
    }

    void GameEngine::fireProjectile() {
        playSoundEffect("res/KirbyStyleLaser.ogg");
        SDL_Surface* surface = IMG_Load("res/projectile.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int projectileWidth = surface->w, projectileHeight = surface->h;
        SDL_Rect projectileRectangle = { getPlayerX() + 30, getPlayerY() + 10, projectileWidth, projectileHeight };
        SDL_FreeSurface(surface);
        Texture projectileTexture = { texture, projectileRectangle, true, true };
        projectiles.emplace_back(projectileTexture);
    }

    void GameEngine::createObjectTexture(std::string path, std::string name, int initialPosX, int initialPosY, bool movable, bool isDrawn)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int textureWidth = surface->w, textureHeight = surface->h;
        SDL_Rect textureRectangle = { initialPosX, initialPosY, textureWidth, textureHeight };
        SDL_FreeSurface(surface);
        Texture myTexture = { texture, textureRectangle, movable, isDrawn };
        gameObjects.insert({ name, myTexture });
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
        Texture txt = { textTexture, textRectangle, false, true };
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
        gameObjects.clear();
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