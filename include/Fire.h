#pragma once
#include "StaticObject.h"
#include "Mage.h"

class Fire : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual void handleCollision(GameObject& character) override;

private:
};