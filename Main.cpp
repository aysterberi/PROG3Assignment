#include <iostream>
#include <string>
#include "GameEngine.h"
#include "Sprite.h"

using namespace SpaceGame;


int main(int argc, char* argv[]) {

    /**
     *   Initiate the engine, outputs a message to the
     *   console if any errors were encountered
     *
     *   Use game settings to specify name of the game, window width, and window height.
     **/

	Engine::GameSettings gameSettings = { "Space Invaders", 800, 600 , 60};
	Engine::GameEngine gameEngine(gameSettings);
	gameEngine.configure(gameSettings);

    if (!gameEngine.init())
        std::cout << "Failed to initialize game engine" << std::endl;
	Engine::Position pos{ 25, 5 };
	Engine::Sprite* sprite = new Engine::Sprite("res/enemy.png", pos, gameEngine);
	gameEngine.addSprite(sprite);
    gameEngine.setPlayerPath("res/ship.png");
    gameEngine.loadBackgroundTexture("res/bg.png");
  //  gameEngine.playBackgroundMusic("res/Solving1.ogg");
    gameEngine.createTextTexture("res/djbgetdigital.ttf", "PRESS 'Y' TO START A NEW GAME", 48, 255, 255, 255);
    gameEngine.setNumberOfEnemies(25);

    gameEngine.gameLoop();

    return 0;
}