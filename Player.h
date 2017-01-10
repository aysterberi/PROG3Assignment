#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
#include <iostream>

namespace SpaceGame {
    class Player : public Engine::Sprite
    {
    public:
        using Sprite::Sprite;
        ~Player();
        void react(SDL_Event& event) override;
	    void move(float timeStep) override;
	    void tick(Engine::GameEngine &) override;
		void hello() { std::cout << "Player is being called" << std::endl; }
    protected:
		bool shooting;
    private:
		float maxSpeed = 20.0;
        void moveLeft();
        void moveRight();
    };
}
#endif
