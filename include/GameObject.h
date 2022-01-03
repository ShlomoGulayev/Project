#pragma once
#include "macros.h"


class GameObject
{
public:
	GameObject(const sf::Vector2f loc, const sf::Texture& texture); 
	void draw(sf::RenderWindow& window);

protected:
	sf::Vector2f m_location;
	sf::Sprite m_sprite;
};