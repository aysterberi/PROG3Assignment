#include "Sprite.h"
#include "GameEngine.h"

namespace Engine {
	//create a sprite with path = file and given position
	Sprite::Sprite(std::string path, Position pos, GameEngine & engine)
	{
		graphic = engine.createGraphic(path);
		position = pos;
		drawn = true;
	}

	//create a sprite that has no assigned graphic
	Sprite::Sprite(Position pos)
	{
		position = pos;
		drawn = false;
	}

	Sprite::~Sprite() {
	}

	SDL_Rect Sprite::getRect()
	{
		SDL_Rect currentRect{ 
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			graphic->width(), 
			graphic->height() };
		return { currentRect };
	}

	void Sprite::setGraphic(GraphicShPtr g)
	{
		//we have a graphic
		drawn = true;
		graphic = g;
	}

	void Sprite::react(SDL_Event& event)
	{
	}
	void Sprite::setVelocity(Velocity velocity)
	{
		this->velocity = velocity;
	}
	void Sprite::setPosition(Position position)
	{
		this->position = position;
	}

	void Sprite::addPositionX(int n)
	{
		position.x += n;
	}

	void Sprite::addPositionY(int n)
	{
		position.y += n;
	}

	void Sprite::move(float dt)
	{
		//move on x-axis
		//position.x += velocity.x * dt;
		//move on y-axis
		//position.y += velocity.y * dt;
	}

	void Sprite::render() const
	{
		if (isDrawn())
			graphic->render(static_cast<int>(position.x), static_cast<int>(position.y));
	}
	void Sprite::tick(GameEngine & engine)
	{

	}
}
