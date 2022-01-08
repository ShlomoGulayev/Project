#include "Ogre.h"
#include "Key.h"

void Ogre::handleCollision(GameObject& character)
{
	if (typeid(character) != typeid(Warrior))
		m_collision = Collisions::REGULAR_COLLISION;
	else 
		m_collision = Collisions::OGRE;
}