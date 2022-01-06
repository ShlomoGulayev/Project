#include "Controller.h"

//------------------------------------------------------
Controller::Controller(sf::RenderWindow& window)
: m_window(&window), m_curr_character(0)
{
    loadTextures();
    m_board.setBoard(m_textures, m_characters, m_gnomes);
}
//------------------------------------------------------
void Controller::run()
{    
    const sf::Time elapsed_time = sf::seconds(0.2f);
    sf::Clock clock;

    while (m_window->isOpen()) 
    {
        m_window->clear(sf::Color::White);
        m_board.draw(*m_window);
        m_window->display();
        
        if (clock.getElapsedTime() > elapsed_time)
            clock.restart();
        
        for (auto event = sf::Event{}; m_window->pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Key::Up || 
                    event.key.code == sf::Keyboard::Key::Down ||
                    event.key.code == sf::Keyboard::Key::Left || 
                    event.key.code == sf::Keyboard::Key::Right)
                {
                    sf::Time deltaTime;
                    deltaTime = clock.restart();
                    m_characters[m_curr_character]->setDirection(event.key.code);
                    m_characters[m_curr_character]->move(deltaTime);
                }
                else {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Key::Escape:
                        m_window->close();
                        break;
                    case sf::Keyboard::Key::P:
                        NextCharacter();
                        break;
                    }
                }
            }
            break;
            }
        }
    }
}

//---------------------------------------------------
void Controller::NextCharacter()
{
    m_curr_character++;
    m_curr_character = m_curr_character % CHARACTERS;
}

//---------------------------------------------------
void Controller::loadTextures()
{
    for (int i = 0; i < NUM_OF_PICS; i++)
        m_textures[i].loadFromFile(object_textures[i]);
}

//---------------------------------------------------
Controller::~Controller()
{
    for (int i = 0; i < m_characters.size(); i++)
        m_characters[i].release();
}