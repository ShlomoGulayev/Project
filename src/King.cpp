#include "King.h"

//---------------------------------------------------
King::King(sf::Vector2f loc, const sf::Texture& texture)
	:MovingObject(loc, texture)
{}

//---------------------------------------------------
void King::handleCollision(MovingObject& character)
{}