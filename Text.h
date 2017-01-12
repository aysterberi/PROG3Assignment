/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#ifndef TEXT_H
#define TEXT_H
#include "Sprite.h"
#include "GameEngine.h"

namespace Engine
{
	class Text :
		public Sprite
	{
	public:
		Text::Text(std::string path, int fontSize, Position pos, SDL_Color color, std::string message, GameEngine& engine);
		~Text();
	};


}
#endif
