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
		void react(SDL_Event& event) override;
		~SecondPlayer();
	};
}


#endif

