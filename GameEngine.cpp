#include "GameEngine.h"



GameEngine::GameEngine() {
    window = NULL;
    surface = NULL;
}

bool GameEngine::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(WINDOW_TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("Unable to create window: %s\n", SDL_GetError());
        return false;
    }

    if (IMG_Init(0) == 0) {
        printf("Unable to initialize SDL_image: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
    }

    if (Mix_Init == 0) {
        printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
    }

    surface = SDL_GetWindowSurface(window);

    return true;
}

SDL_Surface* GameEngine::loadSurface(std::string path) {
    SDL_Surface* adjustedSurface = NULL;
    SDL_Surface* initialSurface = IMG_Load(path.c_str());

    if (initialSurface == NULL) {
        printf("Unable to load image %s: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }

    adjustedSurface = SDL_ConvertSurface(initialSurface, surface->format, 0);
    if (adjustedSurface == NULL) {
        printf("Unable to adjust image %s: %s\n", path.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(initialSurface);
    return adjustedSurface;
}


GameEngine::~GameEngine() {
    SDL_DestroyWindow(window);
    window = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
