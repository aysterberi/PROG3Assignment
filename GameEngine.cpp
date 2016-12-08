#include "GameEngine.h"
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
        const int TPR = 1000; // Time per rotation

        while (!quit) {
            Uint32 nextTick = SDL_GetTicks() + TPR;
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_LCTRL:
                    case SDLK_RCTRL: playSoundEffect("res/KirbyStyleLaser.ogg"); break;
                    case SDLK_y: break;
                    case SDLK_a:
                    case SDLK_LEFT: break;
                    case SDLK_d:
                    case SDLK_RIGHT: break;
                    case SDLK_F8: toggleMusic(); break;
                    }
                }
            }
            renderEverything();
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
        for (Texture var : toRender) {
            SDL_RenderCopy(renderer, var.texture, NULL, &var.dstRect);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_Texture* GameEngine::createObjectTexture(std::string path)
    {
        return nullptr;
    }

    SDL_Texture* GameEngine::createTextTexture(std::string path, std::string message,
        int fontSize, Uint8 rColor, Uint8 gColor, Uint8 bColor) {

        TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
        SDL_Color color = { rColor, gColor, bColor };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textWidth = textSurface->w, textHeight = textSurface->h;
        SDL_Rect textRectangle = { 100, 250, textWidth, textHeight };

        SDL_FreeSurface(textSurface);
        Texture txt = { textTexture, textRectangle };
        toRender.emplace_back(txt);
        return textTexture;
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

    SDL_Renderer* GameEngine::createRenderer(SDL_Window* window) {
        return SDL_CreateRenderer(window, -1, 0);
    }

    GameEngine::~GameEngine() {
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

}