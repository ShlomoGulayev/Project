#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "macros.h"

using std::string;


class Button
{
public:
	Button() = default;
	Button(sf::String text, const sf::Vector2f& pos);
	bool handleClick(const sf::Vector2f& location);
	void draw(sf::RenderWindow& window);
	void setColor(sf::Color color);

private:
	sf::RectangleShape m_button;
	sf::Font m_font;
	sf::Color m_color;
	string m_str;
};
