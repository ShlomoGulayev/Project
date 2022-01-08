#pragma once
#include "StaticObject.h"
#include "King.h"

class Throne : public StaticObject
{
public:
	using StaticObject::StaticObject;
	void handleCollision(GameObject& character) override;

private:
};