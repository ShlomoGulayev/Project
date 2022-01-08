#pragma once
#include <SFML/Graphics.hpp>

//Window related
constexpr auto WINDOW_WIDTH = 1600;
constexpr auto WINDOW_HEIGHT = 800;

//Menu related
constexpr auto NUM_OF_BUTTONS = 3;
constexpr auto BUTTON_SIZE_WIDTH = 300;
constexpr auto BUTTON_SIZE_HEIGHT = 80;

//Board related
constexpr auto BOARD_WIDTH = 1600;
constexpr auto BOARD_HEIGHT = 600;
constexpr auto NUM_OF_PICS = 12;
constexpr auto CHARACTERS = 4;
constexpr auto OBJECT_SIZE_PIXEL = 100;

enum MenuButtons
{
	Start, Instructions, Exit
};

enum Objects
{
	KING, MAGE, WARRIOR, THIEF, OGRE, KEY, TELEPORT, FIRE, THRONE, WALL, GATE, GNOME
};

enum class Collisions
{
	NO_COLLISION, REGULAR_COLLISION, DESTROY, OGRE, WON, TELEPORT
};

const std::string object_textures[NUM_OF_PICS] = { "king.png", 
												   "mage.png", 
												   "warrior.png", 
												   "thief.png",
												   "ogre.png",
												   "key.png",
												   "portal.png",
												   "fire.png", 
												   "throne.png", 
												   "wall.png",
												   "gate.png", 
												   "gnome.png"
												   };