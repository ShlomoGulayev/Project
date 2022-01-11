#pragma once
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include "macros.h"

class Singleton {
public:
	~Singleton();
	static Singleton& instance();
	sf::Sprite getMenuSprite(const int index) const;
	sf::Texture* getObjectTexture(const int index);
	sf::Font* getFont();

private:
	Singleton();
	Singleton(const Singleton&) = default;
	Singleton& operator=(const Singleton&) = default;
	
	void loadTexturesObjects();
	void loadMenuPictures();
	void loadFont();

	sf::Texture m_textures_menu[NUM_OF_MENU_PICS];
	sf::Texture m_textures_objects[NUM_OF_OBJECT_PICS];
	sf::Font m_font;
};