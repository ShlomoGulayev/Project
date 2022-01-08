#include "Throne.h"

void Throne::handleCollision(GameObject& character)
{
	if (typeid(character) != typeid(King))
		m_collision = Collisions::REGULAR_COLLISION;
	else
		m_collision = Collisions::WON;
}

