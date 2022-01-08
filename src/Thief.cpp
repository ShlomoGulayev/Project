#include "Thief.h"

//---------------------------------------------------
Thief::Thief(sf::Vector2f location, const sf::Texture& texture)
	:MovingObject(location, texture), m_key(false)
{}

//---------------------------------------------------
bool Thief::hasKey() const
{
	return m_key;
}
//---------------------------------------------------
void Thief::setKey()
{
	m_key = !m_key;
}
//---------------------------------------------------
void Thief::handleCollision(MovingObject& character)
{}