#include "Mage.h"

//---------------------------------------------------
Mage::Mage(sf::Vector2f loc, const sf::Texture& texture)
	:MovingObject(loc, texture)
{}

//---------------------------------------------------
void Mage::handleCollision(MovingObject& character)
{}
