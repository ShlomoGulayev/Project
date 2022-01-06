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
#include "Gnome.h"

using std::vector;
using std::string;
using std::unique_ptr;


class Board {
public:
	Board();
	void setBoard(sf::Texture textures[], vector< unique_ptr <MovingObject > >& characters, vector< unique_ptr <MovingObject > >& gnomes);
	void draw(sf::RenderWindow& window);
	void createObject(sf::Texture textures[]);

private:
	int m_rows;
	int m_cols;
	
	vector<string> m_board;
	vector< unique_ptr <StaticObject> > m_static_objects;
	vector< unique_ptr <MovingObject > >* m_characters;
	vector< unique_ptr <MovingObject > >* m_gnomes;
	
};