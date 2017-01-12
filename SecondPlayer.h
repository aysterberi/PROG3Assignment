/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

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

