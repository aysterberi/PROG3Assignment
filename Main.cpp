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
     *   Use game settings to specify name of the game, window width, window height, and FPS.
     **/
    GameEngine::GameSettings gameSettings = { "Space Invaders", 800, 600 , 60};
    GameEngine gameEngine(gameSettings);


    if (!gameEngine.init())
        std::cout << "Failed to initialize game engine" << std::endl;

    // Set the path to the png file that will be the player sprite
    gameEngine.setPlayerPath("res/ship.png");

    // Set the path to the png file that will be the enemy sprite
    // TODO: Implement

    // Set the path to the png file that will be the projectile sprite
    // TODO: Implement

    // Set the path to the png file that will be the background
    gameEngine.loadBackgroundTexture("res/bg.png");

    // Set the background music path (OGG format)
    gameEngine.playBackgroundMusic("res/Solving1.ogg");

    // Welcome message (path, message, font size, R, G, B)
    gameEngine.createTextTexture("res/djbgetdigital.ttf", "PRESS 'Y' TO START A NEW GAME", 48, 255, 255, 255);

    // Set the number of enemies
    gameEngine.setNumberOfEnemies(25);

    // Set the enemy speed
    // TODO: Implement

    // Set how much the enemies move down after hitting the edge of the screen
    // TODO: Implement

    // starts the game loop
    gameEngine.gameLoop();

    return 0;
}