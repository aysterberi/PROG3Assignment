#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include <iostream>
#include <string>
#include "GameEngine.h"
#include "Sprite.h"

using namespace Engine;


int main(int argc, char* argv[]) {

    /**
     *   Initiate the engine, outputs a message to the
     *   console if any errors were encountered
     *
     *   Use game settings to specify name of the game, window width, and window height.
     **/
    GameEngine::GameSettings gameSettings = { "Space Invaders", 800, 600 };
    GameEngine gameEngine(gameSettings);


    if (!gameEngine.init())
        std::cout << "Failed to initialize game engine" << std::endl;

    gameEngine.setPlayerPath("res/ship.png");
    gameEngine.loadBackgroundTexture("res/bg.png");
    gameEngine.playBackgroundMusic("res/Solving1.ogg");
    gameEngine.createTextTexture("res/djbgetdigital.ttf", "PRESS 'Y' TO START A NEW GAME", 48, 255, 255, 255);
    gameEngine.setNumberOfEnemies(25);

    gameEngine.gameLoop();

    _CrtDumpMemoryLeaks();
    return 0;
}