#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"

namespace SpaceGame {
    class Player : public Engine::Sprite
    {
    public:
        using Sprite::Sprite;
        ~Player();
        void react(SDL_Event event) override;
        void tick(Engine::GameEngine &) override;
    private:
        void moveLeft();
        void moveRight();
		bool shooting;
    };
}
#endif
