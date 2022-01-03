#pragma once
#include "macros.h"
#include "Controller.h"
#include "Button.h"
#include <string>
#include <vector>

using std::string;
using std::vector;


class Menu
{
public:
	Menu();
	void run();

private:
	void doButton(const int index, bool& instruction_pressed);
	void drawButtons();

	Controller m_controller;
	sf::RenderWindow m_window;
	Button m_buttons[NUM_OF_BUTTONS];
	vector<string> m_texts = { "Start", "Instructions", "Exit" };
	int m_last_button_over = 0;

	sf::Texture m_background;
	sf::Texture m_instruction_pic;
	
};