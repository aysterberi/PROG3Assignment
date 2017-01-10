#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include <iostream>

namespace SpaceGame {
    class Enemy :
        public Engine::Sprite
    {
    public:
		using Sprite::Sprite;
        Enemy(SDL_Texture*, SDL_Rect, bool, int);
        ~Enemy();
        void react(SDL_Event&) override;
        void tick(Engine::GameEngine &engine) override;
        void invertDirection() { direction = -direction; }
		void hello() { std::cout << "Eneemy is being called" << std::endl; }
    private:
        SDL_Texture* texture;
        SDL_Rect rect;
        bool drawn;
		int direction = 3;
    };

}

#endif
