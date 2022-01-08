#include "Controller.h"

//-------------------------------------------------------------------------
Controller::Controller(sf::RenderWindow& window)
: m_window(&window), m_curr_character(0)
{
    loadTextures();
    m_background_pic.loadFromFile("backController.jpg");
    m_board.setBoard(m_textures, m_characters, m_static_objects);
}
//-------------------------------------------------------------------------
void Controller::run()
{    
    const sf::Time elapsed_time = sf::seconds(0.1f);
    sf::Time delta_time;
    sf::Clock clock;
    sf::Sprite background(m_background_pic);
    bool right_pressed[CHARACTERS] = { false };
    sf::Event event;
    m_clock.updateTime(100);

    while (m_window->isOpen()) 
    {
        m_window->clear();
        m_window->draw(background);
        m_board.draw(*m_window);
        m_clock.draw(*m_window);
        m_window->display();
        
        if (m_clock.getTime() <= 0)
        {
            m_window->close();
        }

        while(m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            
            case sf::Event::KeyPressed:
            {                
                switch (event.key.code)
                {
                case sf::Keyboard::Key::Escape:
                    m_window->close();
                    break;

                case sf::Keyboard::Key::P:
                    NextCharacter();
                    break;
                }
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if (!right_pressed[m_curr_character])
                        m_characters[m_curr_character]->rotateSprite(-1, 1);        
                    right_pressed[m_curr_character] = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if(right_pressed[m_curr_character])
                        m_characters[m_curr_character]->rotateSprite(-1, 1);
                    right_pressed[m_curr_character] = false;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {}
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {}

                m_characters[m_curr_character]->setDirection(event.key.code);
            }
            }
        }
        if (clock.getElapsedTime() >= elapsed_time)
            clock.restart();
        
        
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            sf::Vector2f last_location = m_characters[m_curr_character]->getLocation();
            if (!(manageCollision(delta_time, clock)))
                m_characters[m_curr_character]->setLocation(last_location);
        }
    }
}
//-------------------------------------------------------------------------
void Controller::NextCharacter()
{
    m_curr_character++;
    m_curr_character = m_curr_character % CHARACTERS;
}
//-------------------------------------------------------------------------
void Controller::loadTextures()
{
    for (int i = 0; i < NUM_OF_PICS; i++)
        m_textures[i].loadFromFile(object_textures[i]);
}
//-------------------------------------------------------------------------
bool Controller::manageCollision(sf::Time& delta_time, sf::Clock& clock)
{
    delta_time = clock.restart();
    m_characters[m_curr_character]->move(delta_time);

    //collision with boundaries of the board
    auto curr_global_bounds = m_characters[m_curr_character]->getGlobalBoundsSprite();
    if (curr_global_bounds.width + curr_global_bounds.left > WINDOW_WIDTH || 
        curr_global_bounds.left < 0 ||
        curr_global_bounds.height + curr_global_bounds.top > BOARD_HEIGHT || 
        curr_global_bounds.top < 0)
        return false;

    //collision with other characters
    for (auto& character : m_characters)
    {
        if (m_characters[m_curr_character]->checkCollision(*character))
            return false;
    }

    //collision with other static objects
    for (auto& static_object : m_static_objects)
    {
        if (m_characters[m_curr_character]->checkCollision(*static_object))
        {
            m_characters[m_curr_character]->handleCollision(*static_object);
            switch (static_object->getCollision())
            {
            case Collisions::REGULAR_COLLISION:
                return false;

            case Collisions::WON:
                m_window->close();
                return true;

            case Collisions::OGRE:
                m_static_objects.push_back(std::make_unique<Key>(static_object->getLocation(), m_textures[KEY]));
                eraseObject(*static_object);
                return true;

            case Collisions::DESTROY:
                eraseObject(*static_object);
                return true;

            case Collisions::TELEPORT:
            {
                if (!m_characters[m_curr_character]->isOnTeleport())
                {
                    m_characters[m_curr_character]->setLocation(m_board.findNextLocationTeleport(static_object->getLocation()));
                    m_characters[m_curr_character]->setIsOnTeleport(true);
                }
                return true;
            }    
            }
        }
    }
    m_characters[m_curr_character]->setIsOnTeleport(false);
    return true;
}
//-------------------------------------------------------------------------
void Controller::eraseObject(StaticObject& static_object)
{
    for (auto static_ptr = m_static_objects.begin(); static_ptr != m_static_objects.end(); static_ptr++)
    {
        if ((*static_ptr)->getLocation() == static_object.getLocation())
        { 
            m_static_objects.erase(static_ptr);
            break;
        }
    }
}
//-------------------------------------------------------------------------
Controller::~Controller()
{
    for (int i = 0; i < m_characters.size(); i++)
        m_characters[i].release();
}