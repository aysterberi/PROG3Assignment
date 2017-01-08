#pragma once
#include "Sprite.h"
namespace Engine {
    class Enemy :
        public Sprite
    {
    public:
        using Sprite::Sprite;
        ~Enemy();
    };

}