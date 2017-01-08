#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"

namespace Engine {
    class Player : public Sprite
    {
    public:
        using Sprite::Sprite;
        ~Player();
        void react(SDL_Event event) override;
        void tick(GameEngine &) override;
    private:
        void moveLeft();
        void moveRight();
		bool shooting;
    };
}
#endif
