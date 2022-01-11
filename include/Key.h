#pragma once
#include "StaticObject.h"
#include "Thief.h"

class Key : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual void handleCollision(GameObject& character) override;
	virtual void handleCollision(King& character) override;
	virtual void handleCollision(Mage& character) override;
	virtual void handleCollision(Warrior& character) override;
	virtual void handleCollision(Thief& character) override;
	virtual void handleCollision(Gnome& character) override;

private:
};