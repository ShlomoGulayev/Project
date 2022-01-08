#include "MovingObject.h"

//-------------------------------------------------------------------------
void MovingObject::setDirection(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1); break;
	case sf::Keyboard::Key::Left:
		m_direction = sf::Vector2f(-1, 0); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
		m_direction = sf::Vector2f(1, 0); break;
	}
}
//-------------------------------------------------------------------------
void MovingObject::move(sf::Time deltaTime)
{
	const auto speedPerSecond = 200.f;
	m_sprite.move(m_direction * speedPerSecond * deltaTime.asSeconds());
}
//-------------------------------------------------------------------------
void MovingObject::handleCollision(GameObject& game_object)
{
	if (&game_object != this)
		game_object.handleCollision(*this);
}
//-------------------------------------------------------------------------
bool MovingObject::isOnTeleport() const
{
	return m_is_on_teleport;
}
//-------------------------------------------------------------------------
void MovingObject::setIsOnTeleport(const bool is_on)
{
	m_is_on_teleport = is_on;
}
//-------------------------------------------------------------------------
void MovingObject::rotateSprite(const float& new_width_sclae, const float& new_height_sclae)
{
	m_sprite.scale(new_width_sclae, new_height_sclae);
}