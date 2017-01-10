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
	auto engine = Engine::GameEngine::instance();
	engine.configure(gameSettings);

    if (!engine.init())
        std::cout << "Failed to initialize game engine" << std::endl;

    engine.setPlayerPath("res/ship.png");
    engine.loadBackgroundTexture("res/bg.png");
    engine.playBackgroundMusic("res/Solving1.ogg");
    engine.createTextTexture("res/djbgetdigital.ttf", "PRESS 'Y' TO START A NEW GAME", 48, 255, 255, 255);
    engine.setNumberOfEnemies(25);

    engine.gameLoop();

    return 0;
}