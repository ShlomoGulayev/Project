#pragma once
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	using GameObject::GameObject;
	Collisions getCollision();
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
	virtual ~StaticObject() = default;

protected:
	Collisions m_collision ;
};