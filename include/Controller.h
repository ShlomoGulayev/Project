#pragma once
#include <vector>
#include <ctime>
#include "Board.h"
#include "Clock.h"
#include "macros.h"
#include "Singleton.h"

class Controller {
public:
	Controller(sf::RenderWindow& window);
	void run();

private:
	void NextCharacter();
	void manageCollision(sf::Time& deltaTime, sf::Clock& clock);
	bool collisionWithBoundaries(const sf::Vector2f& last_location);
	bool collisionWithCharacters(const sf::Vector2f& last_location);
	bool collisionWithStasticObjects(const sf::Vector2f& last_location);
	void eraseStaticObject(StaticObject& static_object);
	void eraseGnomes();

	Board m_board;
	Clock m_timer;

	sf::RenderWindow *m_window;
	std::vector< std::unique_ptr <MovingObject > > m_characters; 
	std::vector< std::unique_ptr <StaticObject > > m_static_objects;

	int m_curr_character;
};

