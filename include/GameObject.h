#pragma once
#include "macros.h"
class King;
class Mage;
class Warrior;
class Thief;
class Gnome;
class Fire;
class Gate;
class Gift1;
class Gift2;
class Gift3;
class Key;
class Ogre;
class Teleport;
class Throne;
class Wall;

class GameObject
{
public:
	GameObject(const sf::Vector2f& loc, const sf::Texture *texture); 
	void setSpriteScale(const float& new_width_scale, const float& new_height_sclae);
	void draw(sf::RenderWindow& window) const;
	bool checkCollision(const GameObject& other);
	void setLocation(const sf::Vector2f& loc);
	const sf::Vector2f& getLocation() const;
	sf::FloatRect getGlobalBoundsSprite() const;
	virtual ~GameObject() = default;

	virtual void handleCollision(GameObject& other_object) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Warrior& warrior) = 0;
	virtual void handleCollision(Thief& thief) = 0;
	virtual void handleCollision(Gnome& gnome) = 0;
	virtual void handleCollision(Fire&) = 0;
	virtual void handleCollision(Gate&) = 0;
	virtual void handleCollision(Gift1&) = 0;
	virtual void handleCollision(Gift2&) = 0;
	virtual void handleCollision(Gift3&) = 0;
	virtual void handleCollision(Key&) = 0;
	virtual void handleCollision(Ogre&) = 0;
	virtual void handleCollision(Teleport&) = 0;
	virtual void handleCollision(Throne&) = 0;
	virtual void handleCollision(Wall&) = 0;
	
protected:
	sf::Sprite m_sprite;
};