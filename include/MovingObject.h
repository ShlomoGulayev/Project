#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	using GameObject::GameObject;
	virtual void setDirection(const sf::Keyboard::Key& key);
	void rotateSprite(const float& new_width_sclae, const float& new_height_sclae);
	void move(sf::Time deltaTime);
	bool isOnTeleport() const;
	bool isRightPressed() const;
	void setIsOnTeleport(const bool& is_on);
	
	virtual void handleCollision(GameObject&) override {}
	virtual void handleCollision(King&) override {}
	virtual void handleCollision(Mage&) override {}
	virtual void handleCollision(Warrior&) override {}
	virtual void handleCollision(Thief&) override {}
	virtual void handleCollision(Gnome&) override {}
	virtual void handleCollision(Fire&) override {}
	virtual void handleCollision(Gate&) override {}
	virtual void handleCollision(Gift1&) override {}
	virtual void handleCollision(Gift2&) override {}
	virtual void handleCollision(Gift3&) override {}
	virtual void handleCollision(Key&) override {}
	virtual void handleCollision(Ogre&) override {}
	virtual void handleCollision(Teleport&) override {}
	virtual void handleCollision(Throne&) override {}
	virtual void handleCollision(Wall&) override {}
	virtual ~MovingObject() = default;

protected:
	sf::Vector2f m_direction;
	float m_speed_per_second = 150.f;
	bool m_is_on_teleport = false;
	bool m_right_pressed = false;
};