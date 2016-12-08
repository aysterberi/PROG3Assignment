#include <string>
#include "Player.h"
#include "DynamicSprite.h"


namespace Engine {

    Player::Player(std::string name, bool alive, int lives, DynamicSprite playerSprite): playerSprite(rect, texture, numberOfImages) {
        name = name;
        alive = alive;
        lives = lives;
    }

    Player* Player::getInstance(std::string name, bool alive, int lives, DynamicSprite playerSprite)
    {
        return nullptr;
    }

    Player::~Player()
    {
    }
}
