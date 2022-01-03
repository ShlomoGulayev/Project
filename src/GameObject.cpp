#include "GameObject.h"

//---------------------------------------------------
GameObject::GameObject(const sf::Vector2f loc, const sf::Texture& texture)
	:m_location(loc), m_sprite(texture)
{
	m_sprite.setPosition(m_location);
}

//---------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}