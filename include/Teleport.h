#pragma once
#include "StaticObject.h"
#include "Mage.h"

class Teleport : public StaticObject
{
public:
	using StaticObject::StaticObject;
	void handleCollision(GameObject& character) override;

private:
};