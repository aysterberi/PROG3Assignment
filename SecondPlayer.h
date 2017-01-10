#ifndef SECONDPLAYER_H
#define SECONDPLAYER_H
#include "Player.h"

namespace SpaceGame
{
	class SecondPlayer :
		public Player
	{
	public:
		using Player::Player;
		void hello() { std::cout << "Player2 is being called" << std::endl; }
		void react(SDL_Event& event) override;
		~SecondPlayer();
	};
}


#endif

