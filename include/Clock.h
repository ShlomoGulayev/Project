#pragma once
#include <iostream>
#include "macros.h"

class Clock
{
public:
	Clock();
	void setText();
	void updateTime(float time);
	float getTime() const;
	void setTimeLeft(int time);
	void draw(sf::RenderWindow& window);

private:
	sf::Clock m_timer;
	float m_time_left;
	sf::Font m_font;
	sf::Text m_text_timer;
};