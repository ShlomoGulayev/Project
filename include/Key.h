#pragma once
#include "StaticObject.h"
#include "Thief.h"

class Key : public StaticObject
{
public:
	using StaticObject::StaticObject;
	void handleCollision(GameObject& character) override;

private:
};