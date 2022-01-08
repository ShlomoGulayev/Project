#pragma once
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	using GameObject::GameObject;
	virtual void handleCollision(GameObject& character) = 0;
	Collisions getCollision();

protected:
	Collisions m_collision ;
};