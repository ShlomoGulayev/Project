#include "Singleton.h"

Singleton::Singleton()
{
	srand(static_cast<unsigned int>(time(NULL)));
	loadMenuPictures();
	loadTexturesObjects();
	loadFont();
}
//-------------------------------------------------------------------------
Singleton& Singleton::instance()
{
	static Singleton inst;
	return inst;
}
//-------------------------------------------------------------------------
void Singleton::loadMenuPictures()
{
	for (int i = 0; i < NUM_OF_MENU_PICS; i++)
		m_textures_menu[i].loadFromFile(MENU_TEXTURES[i]);
}
//-------------------------------------------------------------------------
void Singleton::loadTexturesObjects()
{
	for (int i = 0; i < NUM_OF_OBJECT_PICS; i++)
		m_textures_objects[i].loadFromFile(OBJECT_TEXTURES[i]);
}
//-------------------------------------------------------------------------
void Singleton::loadFont()
{
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}
//-------------------------------------------------------------------------
sf::Sprite Singleton::getMenuSprite(const int index) const
{
	return sf::Sprite(m_textures_menu[index]);
}
//-------------------------------------------------------------------------
sf::Texture* Singleton::getObjectTexture(const int index) 
{
	return &m_textures_objects[index];
}
//-------------------------------------------------------------------------
sf::Font* Singleton::getFont()
{
	return &m_font;
}
//-------------------------------------------------------------------------
Singleton::~Singleton()
{}
