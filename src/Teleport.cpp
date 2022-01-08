#include "Teleport.h"

void Teleport::handleCollision(GameObject& character)
{
	if (typeid(character) != typeid(Mage))
		m_collision = Collisions::TELEPORT;
	else
		m_collision = Collisions::NO_COLLISION;
}