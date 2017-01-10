#ifndef INVADERS_H
#define INVADERS_H
#include "GameEngine.h"

namespace SpaceGame
{
	class Invaders
	{
	public:
		Invaders();
		void createEnemies(int amount, Engine::GameEngine& context);
		~Invaders();
	};
}

#endif
