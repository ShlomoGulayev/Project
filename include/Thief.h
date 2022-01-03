#pragma once
#include "MovingObject.h"


class Thief : public MovingObject
{
public:
	Thief(sf::Vector2f loc, const sf::Texture& texture);
	bool hasKey();

private:
	bool m_key;
};