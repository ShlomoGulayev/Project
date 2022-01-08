#pragma once
#include "MovingObject.h"

class King : public MovingObject
{
public:
	King(sf::Vector2f loc, const sf::Texture& texture);
	virtual void handleCollision(MovingObject& character) override;

private:
};