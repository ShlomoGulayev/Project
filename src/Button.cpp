#include "Button.h"

//---------------------------------------------------
Button::Button(sf::String text, const sf::Vector2f& position)
    :m_button(sf::Vector2f(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT)), m_str(text)
{
    m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    m_color = sf::Color(204, 0, 0);
    m_button.setPosition(position);
}

//---------------------------------------------------
void Button::draw(sf::RenderWindow& window)
{ 
    // set text
    sf::Text text(m_str, m_font);
    text.setCharacterSize(22);
    text.setColor(sf::Color::White);
    text.setPosition(m_button.getPosition());
    auto textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);

    // set Rectangle
    m_button.setFillColor(m_color);
    m_button.setOutlineColor(sf::Color::Black);
    m_button.setOutlineThickness(2);
    m_button.setOrigin(sf::Vector2f(BUTTON_SIZE_WIDTH / 2, BUTTON_SIZE_HEIGHT / 2));

    window.draw(m_button);
    window.draw(text);
}

//------------------------------------------------------
bool Button::handleClick(const sf::Vector2f& location)
{
    if (m_button.getGlobalBounds().contains(location))
        return true;

    return false;
}

//------------------------------------------------------
void Button::setColor(sf::Color color)
{
    m_color = color;
}
