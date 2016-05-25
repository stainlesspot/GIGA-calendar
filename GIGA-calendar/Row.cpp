

#include "Row.h"
#include "Settings.h"
#include "Resources.h"
#include <iostream>

void Row::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int kon = 0;
	for (auto it(week.begin()), end(week.end()); it != end; it++) {
		target.draw(*it, states);
		kon++;
	}
	std::cout << "Kon " << kon << std::endl;
}

Row::Row(const sf::Vector2f position, const uint16_t width, const uint16_t height, const Date & date, const std::array<gui::Button, 7>& week)
	: week(week)
{
	/*
	uint8_t dayOfWeek(date.getDayOfWeek()), i = 0;

	const unsigned int buttonWidth = (width - 6 * Settings::spaceBetweenCells) / 7;
	sf::Image buttonImage;
	buttonImage.create(buttonWidth, height, Settings::cellColor);
	sf::Texture buttonTexture;
	buttonTexture.loadFromImage(buttonImage);

	for (auto it(week.begin()), end(week.end()); it != end; it++, i++) {
		it->setName(gui::TextArea(std::to_string((date - dayOfWeek + i).getDay()), Resources::arial).setColor(sf::Color::Black))
			.setTexture(buttonTexture)
			.setPosition(position + sf::Vector2f((buttonWidth + Settings::spaceBetweenCells) * i, 0));
	}*/
}
