#include "Fire.h"

void Fire::handleCollision(GameObject& character)
{
	if (typeid(character) != typeid(Mage))
		m_collision = Collisions::REGULAR_COLLISION;
	else
		m_collision = Collisions::DESTROY;
}
