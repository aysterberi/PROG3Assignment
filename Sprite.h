#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "SmartPointers.h"
#include <iostream>

namespace Engine {
	class GameEngine;

	struct Position
	{
		float x;
		float y;
	};
	struct Velocity
	{
		float x; //positive is right, negative is left
		float y; //positive is down, negative is up
	};
	class Sprite {
	public:
		Sprite(std::string path, Position, GameEngine& engine);
		Sprite(Position pos);
		virtual ~Sprite();
		SDL_Texture* getTexture() const { return graphic->texture(); }
		SDL_Rect getRect();
		void setGraphic(GraphicShPtr graphic);
		void setRectY(int newY) { rect.y = newY; }
		void setRectX(int newX) { rect.x = newX; }
		void incrementRectX(int inc);
		void incrementRectY(int inc);
		bool isDrawn() const { return drawn; }
		void setDrawn(bool newValue) { drawn = newValue; }
		virtual void react(SDL_Event& event);
		void render() const;
		virtual void tick(GameEngine& engine);
		virtual Position getPosition() { return position;  }
		virtual void setPosition(Position position);
		virtual void addPositionX(int n);
		virtual void addPositionY(int y);
		virtual Velocity getVelocity() { return velocity;  }
		virtual void setVelocity(Velocity velocity);
		virtual void move(float dt);
		virtual void hello() { std::cout << "Sprite is being called" << std::endl; }
		//deleting copy, assign constructors 
		//to prevent value semantics
		//i.e. enforce pointers and refs
		Sprite(const Sprite &other) = delete;
		Sprite& operator=(Sprite const &obj) = delete;

	private:
		TextureShPtr texture_sh;
		GraphicShPtr graphic;
		SDL_Texture* texture;
		int height;
		int width;
		SDL_Rect rect;
		bool drawn;
		Velocity velocity;
		Position position;
	};
}
#endif

