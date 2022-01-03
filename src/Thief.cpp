#include "Thief.h"

//---------------------------------------------------
Thief::Thief(sf::Vector2f location, const sf::Texture& texture)
	:MovingObject(location, texture), m_key(false)
{}

//---------------------------------------------------
bool Thief::hasKey()
{
	return m_key;
}