#pragma once
#include "MovingObject.h"

class Thief : public MovingObject
{
public:
	Thief(sf::Vector2f loc, const sf::Texture& texture);
	virtual void handleCollision(MovingObject& character) override;
	bool hasKey() const;
	void setKey();

private:
	bool m_key;
};