#include "Invaders.h"
#include <iostream>
#include "SecondPlayer.h"


namespace SpaceGame
{
	Invaders::Invaders()
	{

		//Configure the settings
		Engine::GameSettings settings = { "Space Invaders II - The Recodening", 800, 600, 20 };

		//Create the engine
		Engine::GameEngine engine(settings);
		
		//Start the engine and its subsystems
		if (!engine.init())
			std::cout << "Something broke real good." << std::endl;

		//Set background assets
		engine.setBackground("res/bg.png");
		engine.setBackgroundMusic("res/Solving1.ogg");

		//create the players (could be extracted to own function)
		Engine::Position startPosition{ 360, 500 }, secondPosition{400, 430};
		Player* player = new Player("res/ship.png", startPosition, engine);
		SecondPlayer* player2 = new SecondPlayer("res/ship.png", secondPosition, engine);

		//add them to the engine
		engine.addSprite(player);
		engine.addSprite(player2);

		//create our enemies
		createEnemies(25, engine);

		//start the loop
		engine.loop();
	}

	void Invaders::createEnemies(int amount, Engine::GameEngine& context)
	{
		Engine::Position enemyPosition{ 25,5 };
		Enemy* enemy = nullptr;
		for (auto i = 0; i < amount; i++)
		{
			enemy = new Enemy("res/enemy.png", enemyPosition, context);
			context.addSprite(enemy);
			enemyPosition.x += 70;
			if (i != 0 && i % 10 == 0)
			{
				enemyPosition.x = 25;
				enemyPosition.y += 70;
			}
		}
	}

	Invaders::~Invaders()
	{
	}

}
