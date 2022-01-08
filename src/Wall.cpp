#include "Wall.h"

void Wall::handleCollision(GameObject& character)
{
	m_collision = Collisions::REGULAR_COLLISION;
}