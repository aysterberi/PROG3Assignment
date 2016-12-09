#include "GameObject.h"
#include "GameEngine.h"
namespace Engine {
    GameObject::GameObject(const SDL_Rect& rect) :
        rect(rect) {
    }


    GameObject::~GameObject() {
    }
}