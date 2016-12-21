#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "GameEngine.h"
using namespace Engine;


int main(int argc, char* argv[]) {

    /**
     *   Initiate the engine, outputs a message to the
     *   console if any errors were encountered
     **/
    GameEngine::GameSettings gameSettings = { "Space Invaders", 800, 600 };
    GameEngine gameEngine(gameSettings);
    if (!gameEngine.init())
        std::cout << "Failed to initialize game engine" << std::endl;

    gameEngine.loadBackgroundTexture("res/bg.png");
    gameEngine.setPlayerPath("res/ship.png");
    gameEngine.playBackgroundMusic("res/Solving1.ogg");
    gameEngine.createTextTexture("res/djbgetdigital.ttf", "PRESS 'Y' TO START A NEW GAME", 48, 255, 255, 255);
    gameEngine.setNumberOfEnemies(25);

    gameEngine.gameLoop();

    return 0;
}

