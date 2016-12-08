#include <string>
#include "Player.h"
#include "DynamicSprite.h"


namespace Engine {

    Player::Player(std::string name, bool alive, int lives, DynamicSprite* playerSprite) {
        name = name;
        alive = alive;
        lives = lives;
        playerSprite = new DynamicSprite(rect, texture, numberOfImages);
    }

    Player* Player::getInstance(std::string name, bool alive, int lives, DynamicSprite* playerSprite) {
        return new Player(name, alive, lives, playerSprite);
    }

    Player::~Player()
    {
    }
}
