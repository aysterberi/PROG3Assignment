#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"

namespace SpaceGame {
    class Player : public Engine::Sprite
    {
    public:
        using Sprite::Sprite;
        ~Player();
        void react(SDL_Event& event) override;
	    void move(float timeStep) override;
	    void tick(Engine::GameEngine &) override;
    private:
		float maxSpeed = 20.0;
        void moveLeft();
        void moveRight();
		bool shooting;
    };
}
#endif
