#include "Sprite.h"
#include "GameEngine.h"

namespace Engine {
	Sprite::Sprite(std::string path, Position)
	{
		auto engine = GameEngine::instance();
		texture_sh = engine.createTexture(path);
	}
	Sprite::Sprite(SDL_Texture * SpTexture,
        SDL_Rect SpDstRect,
        bool SpDrawn = true) 
        : texture(SpTexture), rect(SpDstRect), drawn(SpDrawn) {

    }

    Sprite::~Sprite() {		
		SDL_DestroyTexture(texture);
    }

    void Sprite::incrementRectX(int inc) {
        rect.x += inc;
    }

    void Sprite::incrementRectY(int inc) {
        rect.y += inc;
    }
	void Sprite::react(SDL_Event event)
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
	void Sprite::move(float dt)
	{
		//move on x-axis
		position.x += velocity.x * dt;
		//move on y-axis
		position.y += velocity.y * dt;
	}

	void Sprite::tick(GameEngine & engine)
	{
	}
}
