#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"

namespace Engine {
    class Player : public Engine::Sprite
    {
    public:
        using Sprite::Sprite;
        Player(Sprite*);
        ~Player();
        void react(SDL_Event event) override;
        void tick(GameEngine &) override;
    private:
        void moveLeft();
        void moveRight();
        void shoot();
    };
}
#endif
