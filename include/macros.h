#pragma once

#include <SFML/Graphics.hpp>

constexpr auto WINDOW_WIDTH = 1600;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto NUM_OF_BUTTONS = 3;
constexpr auto NUM_OF_PICS = 12;
constexpr auto CHARACTERS = 4;
constexpr auto BUTTON_SIZE_WIDTH = 300;
constexpr auto BUTTON_SIZE_HEIGHT = 80;
constexpr auto BOARD_WIDTH = 1600;
constexpr auto BOARD_HEIGHT = 600;

constexpr auto Start = 0;
constexpr auto Instructions = 1;
constexpr auto Exit = 2;

constexpr auto KING = 0;
constexpr auto MAGE = 1;
constexpr auto WARRIOR = 2;
constexpr auto THIEF = 3;
constexpr auto ORGE = 4;
constexpr auto KEY = 5;
constexpr auto PORTAL = 6;
constexpr auto FIRE = 7;
constexpr auto THRONE = 8;
constexpr auto WALL = 9;
constexpr auto GATE = 10;
constexpr auto GNOME = 11;

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