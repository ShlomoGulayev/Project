#include "MovingObject.h"

//---------------------------------------------------
void MovingObject::setDirection(sf::Keyboard::Key key)
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

//---------------------------------------------------
void MovingObject::move(sf::Time deltaTime)
{
	const auto speedPerSecond = 100.f;
	m_sprite.move(m_direction * speedPerSecond * deltaTime.asSeconds());
	m_location += m_direction;
}
