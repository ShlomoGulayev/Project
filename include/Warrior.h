#pragma once
#include "MovingObject.h"


class Warrior : public MovingObject
{
public:
	Warrior(sf::Vector2f loc, const sf::Texture& texture);
	virtual void handleCollision(MovingObject& character) override;

private:
};