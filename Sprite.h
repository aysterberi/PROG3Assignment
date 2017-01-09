#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

namespace Engine {
	class GameEngine;

	class Sprite {
	public:
		Sprite(SDL_Texture*, SDL_Rect, bool);
		virtual ~Sprite();
		SDL_Texture* getTexture() const { return texture; }
		SDL_Rect getRect() const { return rect; }
		void setRectY(int newY) { rect.y = newY; }
		void setRectX(int newX) { rect.x = newX; }
		void incrementRectX(int inc);
		void incrementRectY(int inc);
		bool isDrawn() const { return drawn; }
		void setDrawn(bool newValue) { drawn = newValue; }
		virtual void react(SDL_Event event);
		virtual void tick(GameEngine& engine);

		//deleting copy, assign constructors 
		//to prevent value semantics
		//i.e. enforce pointers and refs
		Sprite(const Sprite &other) = delete;
		Sprite& operator=(Sprite const &obj) = delete;

	private:
		SDL_Texture* texture;
		SDL_Rect rect;
		bool drawn;
	};
}
#endif

