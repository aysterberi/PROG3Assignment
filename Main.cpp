#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "GameEngine.h"


int main(int argc, char* argv[]) {

    /**
     *   Initiate the engine, outputs a message to the
     *   console if any errors were encountered
     **/
    GameEngine::GameSettings gameSettings = { "Space Invaders", 800, 600 };
    GameEngine gameEngine(gameSettings);
    if (!gameEngine.init())
        std::cout << "Failed to initialize game engine" << std::endl;

    gameEngine.surface = gameEngine.loadSurface("res/bg.png");
    gameEngine.updateBackground();
    gameEngine.playBackgroundMusic("res/Solving1.ogg");
    gameEngine.createText("res/djbgetdigital.ttf", "Hello!", 48, 255, 255, 255);

    SDL_RenderClear(gameEngine.renderer);
    SDL_RenderCopy(gameEngine.renderer, gameEngine.textTexture, NULL, &gameEngine.textRectangle);
    SDL_RenderPresent(gameEngine.renderer);

    SDL_Delay(2000);

    return 0;
}

