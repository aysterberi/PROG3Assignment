/*
* Billy G. J. Beltran(bibe1744) & Joakim Berglund(jobe7147)
* Contact details: billy@caudimordax.org, joakimberglund@live.se
*/

#include "Text.h"

namespace Engine
{


	Text::Text(std::string path, int fontSize, Position pos, SDL_Color color, std::string message, GameEngine & engine): Sprite(pos)
	{
		TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
		GraphicShPtr g = engine.createTextGraphic(font, message, color);
		setGraphic(g);
	}

	Text::~Text()
	{
	}

}