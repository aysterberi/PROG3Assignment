#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"

namespace Engine {
    class Player : public Sprite
    {
    public:
        Player(SDL_Texture*, SDL_Rect, bool);
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
