#include "Menu.h"

//---------------------------------------------------
Menu::Menu()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Save The King"), m_controller(m_window)
{
    for (int i = 0; i < NUM_OF_BUTTONS; i++)
        m_buttons[i] = Button(m_texts[i], sf::Vector2f(WINDOW_WIDTH/2, 300 + i * 150));
 
    m_instruction_pic.loadFromFile("instructions.png");   
    m_background.loadFromFile("back.gif");
}

//--------------------------------------------------------
void Menu::run()
{
    sf::Sprite background_pic(m_background);
    background_pic.setScale(3.75, 3.25);
    sf::Sprite instruction_pic(m_instruction_pic);
    instruction_pic.setPosition(250, 100);
    
    bool instructions_pressed = false;
    
    while (m_window.isOpen())
    {
        m_window.clear();
        m_window.draw(background_pic);
        drawButtons();
        
        if (instructions_pressed)
            m_window.draw(instruction_pic);

        m_window.display();

        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            
            case sf::Event::MouseButtonReleased:
            {
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                {
                    instructions_pressed = false;
                    auto location = sf::Mouse::getPosition(m_window);
                    for (int i = 0; i < NUM_OF_BUTTONS; i++)
                    {
                        if (m_buttons[i].handleClick((sf::Vector2f)location))
                            doButton(i, instructions_pressed);
                    }
                }
                break;
                }
            break;
            }
            case sf::Event::MouseMoved:
            {
                auto location = sf::Mouse::getPosition(m_window); 
                m_buttons[m_last_button_over].setColor(sf::Color(204, 0, 0));
                for (int i = 0; i < NUM_OF_BUTTONS; i++)
                {
                    if (m_buttons[i].handleClick((sf::Vector2f)location))
                    {
                        m_buttons[i].setColor(sf::Color(255, 0, 0));
                        m_last_button_over = i;
                    }
                }
                break;
            }
            }
        }
    }
}

//--------------------------------------------------------
void Menu::drawButtons()
{
    for (int i = 0; i < NUM_OF_BUTTONS; i++)
        m_buttons[i].draw(m_window);
}

//--------------------------------------------------------
void Menu::doButton(const int index, bool &instruction_pressed)
{
    switch(index)
    {
    case Start:
        m_controller.run();
        break;

    case Instructions:
        instruction_pressed = true;
        break;

    case Exit:
        m_window.close();
        break;
    }
}
