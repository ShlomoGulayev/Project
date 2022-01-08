#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	using GameObject::GameObject;
	void setDirection(const sf::Keyboard::Key& key);
	void rotateSprite(const float& new_width_sclae, const float& new_height_sclae);
	void move(sf::Time deltaTime);
	
	virtual void handleCollision(GameObject& game_object);
	virtual void handleCollision(MovingObject& character) = 0;
	
	bool isOnTeleport() const;
	void setIsOnTeleport(const bool is_on);

protected:
	sf::Vector2f m_direction;
	bool m_is_on_teleport = false;
};