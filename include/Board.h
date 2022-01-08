#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <memory>
#include "macros.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "King.h"
#include "Mage.h"
#include "Warrior.h"
#include "Thief.h"
#include "Teleport.h"
#include "Key.h"
#include "Wall.h"
#include "Throne.h"
#include "Gate.h"
#include "Ogre.h"
#include "Fire.h"


class Board {
public:
	Board();
	void setBoard(sf::Texture textures[], 
				  std::vector< std::unique_ptr <MovingObject > > &characters, 
				  std::vector< std::unique_ptr <StaticObject > > &static_objects);
	void draw(sf::RenderWindow& window) const;
	const sf::Vector2f& findNextLocationTeleport(const sf::Vector2f& loc);
	float getWidthObject() const;
	float getHeightObject() const;

private:
	void createObject(sf::Texture textures[]);
	void resizeObjects();

	int m_rows;
	int m_cols;
	float m_height_object_scale;
	float m_width_object_scale;
	
	std::vector< std::string> m_board;
	std::vector< std::unique_ptr <StaticObject > >* m_static_objects;
	std::vector< std::unique_ptr <MovingObject > >* m_characters;
	std::vector <std::unique_ptr <sf::Vector2f > > m_teleports;
};