#pragma once
#include <iostream>
#include "macros.h"
#include "Singleton.h"

class Clock
{
public:
	Clock();
	void updateTime(float time);
	void updateLevel();
	float getTime() const;
	void setTimeLeft(const float& time);
	void draw(sf::RenderWindow& window);

private:
	void setText();

	int m_level;
	sf::Clock m_timer;
	float m_time_left;
	sf::Text m_text_timer;
};