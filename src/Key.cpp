#include "Key.h"

void Key::handleCollision(GameObject& character)
{
	if (typeid(character) == typeid(Thief))
	{
		Thief* thief = dynamic_cast<Thief*> (&character);
		if (!thief->hasKey())
		{
			thief->setKey();
			m_collision = Collisions::DESTROY;
		}
	}
	else
		m_collision = Collisions::NO_COLLISION;
}