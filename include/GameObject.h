#pragma once
#include "macros.h"

class GameObject
{
public:
	GameObject(const sf::Vector2f& loc, const sf::Texture& texture); 
	void draw(sf::RenderWindow& window) const;
	virtual void handleCollision(GameObject& player) = 0;
	bool checkCollision(const GameObject& other);
	void setSpriteScale(const float& new_width_scale,const float& new_height_sclae);
	//void rotateSprite(const float& new_width_sclae, const float& new_height_sclae);
	void setLocation(const sf::Vector2f& loc);
	const sf::Vector2f& getLocation() const;
	sf::FloatRect getGlobalBoundsSprite() const;

protected:
	sf::Sprite m_sprite;
};