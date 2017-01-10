#include "Sprite.h"
#include "GameEngine.h"

namespace Engine {
	Sprite::Sprite(std::string path, Position pos, GameEngine & engine)
	{
		graphic = engine.createGraphic(path);
		position = pos;
		drawn = true;
	}
	Sprite::Sprite(SDL_Texture * SpTexture,
		SDL_Rect SpDstRect,
		bool SpDrawn = true)
		: texture(SpTexture), rect(SpDstRect), drawn(SpDrawn) {

	}

	Sprite::~Sprite() {
		SDL_DestroyTexture(texture);
	}

	SDL_Rect Sprite::getRect()
	{
		SDL_Rect currentRect{ 
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			graphic->width(), 
			graphic->height() };
		std::cout << "Graphic size is " << graphic->width() << "w, " << graphic->height() << "h." << std::endl;
		return { currentRect };
	}

	void Sprite::incrementRectX(int inc) {
		position.x += inc;
	}

	void Sprite::incrementRectY(int inc) {
		position.y += inc;
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
