#include "Clock.h"

Clock::Clock() 
{
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	setText();
}
//-------------------------------------------------------------------------
void Clock::setText()
{
	m_text_timer.setFont(m_font);
	int size = 40;
	m_text_timer.setCharacterSize(size);
	m_text_timer.setPosition(100, BOARD_HEIGHT + (WINDOW_HEIGHT - BOARD_HEIGHT) / 2 - size/2);
	m_text_timer.setColor(sf::Color::Red);
	m_text_timer.setOutlineColor(sf::Color::Black);
	m_text_timer.setOutlineThickness(3);
}
//-------------------------------------------------------------------------
void Clock::updateTime(float time)
{

	m_time_left += time;
	m_time_left -= m_timer.getElapsedTime().asSeconds();
	int minutes = m_time_left / 60;
	int seconds = (int)m_time_left % 60;
	m_text_timer.setString("Time left: " + 
						  (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes)) + ":" +
						  (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds)));
	m_timer.restart();
}
//-------------------------------------------------------------------------
float Clock::getTime() const
{
	return m_time_left;
}
//-------------------------------------------------------------------------
void Clock::setTimeLeft(int time)
{
	m_time_left = time;
}
//-------------------------------------------------------------------------
void Clock::draw(sf::RenderWindow& window)
{
	updateTime(0);
	window.draw(m_text_timer);
}