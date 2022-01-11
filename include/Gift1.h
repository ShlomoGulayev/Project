#pragma once
#include "Gift.h"

class Gift1 : public Gift
{
public:
	using Gift::Gift;
	virtual void handleCollision(GameObject& character) override;
	virtual void handleCollision(King& king) override;
	virtual void handleCollision(Mage& mage) override;
	virtual void handleCollision(Warrior& warrior) override;
	virtual void handleCollision(Thief& thief) override;
	virtual void handleCollision(Gnome& gnome) override;
private:
};