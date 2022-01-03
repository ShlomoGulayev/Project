#pragma once
#include "GameObject.h"


class MovingObject : public GameObject
{
public:
	using GameObject::GameObject;
	void setDirection(sf::Keyboard::Key key);
	void move(sf::Time deltaTime);
	
protected:
	sf::Vector2f m_direction;
};