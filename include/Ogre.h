#pragma once
#include "StaticObject.h"
#include "Warrior.h"

class Ogre : public StaticObject
{
public:
	using StaticObject::StaticObject;
	void handleCollision(GameObject& character) override;

private:
};