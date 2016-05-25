#include "Resources.h"

sf::Font Resources::arial;
sf::Texture Resources::calendarCell;

void Resources::loadCalendarCell(unsigned int width, unsigned int height)
{
	sf::Image i;
	i.create(width, height, sf::Color::White);
	calendarCell.loadFromImage(i);
}

void Resources::load()
{
	arial.loadFromFile("arial.ttf");
}
