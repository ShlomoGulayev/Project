#include "Gate.h"

void Gate::handleCollision(GameObject& character)
{
	if (typeid(character) != typeid(Thief))
		m_collision = Collisions::REGULAR_COLLISION;
	else
	{
		Thief* thief = dynamic_cast<Thief*> (&character);
		if (thief->hasKey())
		{
			m_collision = Collisions::DESTROY;
			thief->setKey();
		}
		else
			m_collision = Collisions::REGULAR_COLLISION;
	}
		

}
