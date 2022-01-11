#include "Controller.h"

//-------------------------------------------------------------------------
Controller::Controller(sf::RenderWindow& window)
:m_window(&window), m_curr_character(0)
{
    m_board.setBoard(m_characters, m_static_objects);
}
//-------------------------------------------------------------------------
void Controller::run()
{    
    //Clock related
    const sf::Time elapsed_time = sf::seconds(0.1f);
    sf::Time delta_time, delta_time_gnomes;
    std::vector< sf::Clock > clock_gnomes;
    sf::Clock clock;
    for (int i = 0; i < m_board.getGnomeSize(); i++)
    {
        clock_gnomes.push_back(sf::Clock());
        m_characters[m_board.getGnome(i)]->setDirection(sf::Keyboard::Key::Left);
    }
    m_timer.updateLevel();
    m_timer.updateTime(50);

    //initialize things before running the program
    sf::Sprite background = Singleton::instance().getMenuSprite(CONTROLLER_PIC);;
    sf::Event event;

    while (m_window->isOpen()) 
    {
        m_window->clear();
        m_window->draw(background);
        m_board.draw(*m_window);
        m_timer.draw(*m_window);
        m_window->display();
        
        if (m_timer.getTime() <= 0)
        {
            m_window->clear();
            return;
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
                m_characters[m_curr_character]->setDirection(event.key.code);
                break;
            }
            }
        }
        if (clock.getElapsedTime() >= elapsed_time)
            clock.restart();
          
        if (event.type == sf::Event::KeyPressed)
            manageCollision(delta_time, clock);

        for (int i = 0; i < m_board.getGnomeSize(); i++)
        {
            int temp = m_curr_character;
            m_curr_character = m_board.getGnome(i);
            manageCollision(delta_time_gnomes, clock_gnomes[i]);
            m_curr_character = temp;
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
void Controller::manageCollision(sf::Time& delta_time, sf::Clock& clock)
{
    sf::Vector2f last_location = m_characters[m_curr_character]->getLocation();
    delta_time = clock.restart();
    m_characters[m_curr_character]->move(delta_time);

    if (collisionWithBoundaries(last_location))
        return;
    if (collisionWithCharacters(last_location))
        return;
    if (collisionWithStasticObjects(last_location))
        return;
    
    if(m_characters[m_curr_character]->isOnTeleport())
        m_characters[m_curr_character]->setIsOnTeleport(false);
    return ;
}
//-------------------------------------------------------------------------
void Controller::eraseStaticObject(StaticObject& static_object)
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
void Controller::eraseGnomes()
{
    std::vector<std::unique_ptr<MovingObject>> vec_tmp;
    for (auto moving_ptr = m_characters.begin(); moving_ptr != m_characters.end(); moving_ptr++)
    {
        if (typeid(**moving_ptr) != typeid(Gnome))
            vec_tmp.push_back(std::move(*moving_ptr));
    }
    
    m_characters.clear();
    m_board.eraseGnomes();

    for (auto moving_ptr = vec_tmp.begin(); moving_ptr != vec_tmp.end(); moving_ptr++)
        m_characters.push_back(std::move(*moving_ptr));
    
}
//-------------------------------------------------------------------------
bool Controller::collisionWithBoundaries(const sf::Vector2f& last_location)
{
    auto curr_global_bounds = m_characters[m_curr_character]->getGlobalBoundsSprite();
    if (curr_global_bounds.width + curr_global_bounds.left > WINDOW_WIDTH ||
        curr_global_bounds.left < 0 ||
        curr_global_bounds.height + curr_global_bounds.top > BOARD_HEIGHT ||
        curr_global_bounds.top < 0)
    {
        m_characters[m_curr_character]->setLocation(last_location);
        if (typeid(*m_characters[m_curr_character]) == typeid(Gnome))
            m_characters[m_curr_character]->setDirection(sf::Keyboard::Down);
        return true;
    }
    return false;
}
//-------------------------------------------------------------------------
bool Controller::collisionWithCharacters(const sf::Vector2f& last_location)
{
    for (auto& character : m_characters)
    {
        if (m_characters[m_curr_character]->checkCollision(*character))
        {
            m_characters[m_curr_character]->setLocation(last_location);
            if (typeid(*m_characters[m_curr_character]) == typeid(Gnome))
                m_characters[m_curr_character]->setDirection(sf::Keyboard::Down);
            return true;
        }
    }
    return false;
}
//-------------------------------------------------------------------------
bool Controller::collisionWithStasticObjects(const sf::Vector2f& last_location)
{
    for (auto& static_object : m_static_objects)
    {
        if (m_characters[m_curr_character]->checkCollision(*static_object))
        {
            m_characters[m_curr_character]->handleCollision(*static_object);
            switch (static_object->getCollision())
            {
            case Collisions::REGULAR_COLLISION:
                m_characters[m_curr_character]->setLocation(last_location);
                if (typeid(*m_characters[m_curr_character]) == typeid(Gnome))
                    m_characters[m_curr_character]->setDirection(sf::Keyboard::Down);
                return true;

            case Collisions::WON:
                //m_window->close();
                return true;

            case Collisions::OGRE:
                m_static_objects.push_back(std::make_unique<Key>(static_object->getLocation(), Singleton::instance().getObjectTexture(KEY)));
                eraseStaticObject(*static_object);
                return true;

            case Collisions::DESTROY:
                eraseStaticObject(*static_object);
                return true;

            case Collisions::TELEPORT:
            {
                for (auto& character : m_characters)
                {
                    if (character->isOnTeleport())
                        return true;
                }
                m_characters[m_curr_character]->setLocation(m_board.findNextLocationTeleport(static_object->getLocation()));
                m_characters[m_curr_character]->setIsOnTeleport(true);
                return true;
            }
            case Collisions::GIFT1:
                eraseStaticObject(*static_object);
                m_timer.setTimeLeft(ADD_TIME);
                return true;
            case Collisions::GIFT2:
                eraseStaticObject(*static_object);
                m_timer.setTimeLeft(-ADD_TIME);
                return true;
            case Collisions::GIFT3:
                eraseStaticObject(*static_object);
                eraseGnomes();
                return true;
            }
        }
    }
    return false;
}