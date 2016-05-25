#pragma once

#include <SFML/Graphics.hpp>

struct Resources {
	static sf::Font arial;
	static sf::Texture calendarCell;

	static void loadCalendarCell(unsigned int width, unsigned int height);

	static void load();
};