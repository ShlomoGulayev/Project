#pragma once
#include <vector>
#include <ctime>
#include "Board.h"
#include "Clock.h"
#include "macros.h"


class Controller {
public:
	Controller(sf::RenderWindow& window);
	void run();
	~Controller();

private:
	void loadTextures();
	void NextCharacter();
	bool manageCollision(sf::Time& deltaTime, sf::Clock& clock);
	void eraseObject(StaticObject& staticObj);

	sf::RenderWindow* m_window;
	Board m_board;
	Clock m_clock;
	
	std::vector< std::unique_ptr <MovingObject > > m_characters; 
	std::vector< std::unique_ptr <StaticObject > > m_static_objects;
	
	sf::Texture m_background_pic;
	sf::Texture m_textures[NUM_OF_PICS];
	int m_curr_character;
};

