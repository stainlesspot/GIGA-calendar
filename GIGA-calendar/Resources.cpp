#include "Resources.h"
#include <memory>

sf::Font Resources::arial;

sf::Texture Resources::Calendar::background,
	Resources::Calendar::Cell::background,
	Resources::Calendar::MonthScroll::Previous::background,
	Resources::Calendar::MonthScroll::Next::background,
	Resources::ActivityMenu::background;

std::unique_ptr<Date> Resources::Calendar::Cell::highlighted(nullptr);

bool Resources::load()
{
	return arial.loadFromFile("resources/arial.ttf");
}

bool Resources::Calendar::loadBackground(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
{	
	sf::Image i;
	i.create(width, height, backgroundColor);

	return background.loadFromImage(i);
}

bool Resources::Calendar::Cell::loadBackground(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
{
	sf::Image i;
	i.create(width, height, backgroundColor);

	return background.loadFromImage(i);
}

bool Resources::ActivityMenu::loadBackground(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
{
	sf::Image i;
	i.create(width, height, backgroundColor);

	return background.loadFromImage(i);

}

bool Resources::Calendar::MonthScroll::Previous::loadBackground()
{
	return background.loadFromFile("resources/arrow_up.png");
}

bool Resources::Calendar::MonthScroll::Next::loadBackground()
{
	return background.loadFromFile("resources/arrow_down.png");
}
