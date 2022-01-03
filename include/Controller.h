#pragma once
#include <vector>
#include <memory>
#include <ctime>
#include "Board.h"
#include "macros.h"


class Controller {
public:
	Controller(sf::RenderWindow& window);
	void run();
	~Controller();

private:
	void loadTextures();
	void NextCharacter();

	sf::RenderWindow* m_window;
	Board m_board;
	std::vector< std::unique_ptr <MovingObject > > m_characters; 
	
	sf::Texture m_textures[NUM_OF_PICS];
	int m_curr_character;
};

