#include "GameObject.h"
#include "GameEngine.h"
namespace Engine {
    GameObject::GameObject(const SDL_Rect& rect) :
        rect(rect) {
    }


	void GameObject::setPosition(int xPos, int yPos)
	{
		objectPosition.xPos = xPos;
		objectPosition.yPos = yPos;
	}

	GameObject::Position GameObject::getPosition()
	{
		return objectPosition;
	}

    GameObject::~GameObject() {
    }
}