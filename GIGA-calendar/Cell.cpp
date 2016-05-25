#include "Cell.h"

Cell::Cell(const Date & date)
	: Button()
{
	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");

	setName(gui::TextArea(std::to_string(date.getDay()), fontArial).setColor(sf::Color::Black));
	setColor(sf::Color(40, 255, 40, 255));
	
}
