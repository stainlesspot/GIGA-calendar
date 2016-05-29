#include "Resources.h"
#include <memory>

sf::Font Resources::arial;
sf::Texture Resources::DateCalendar::background,
	Resources::DateCalendar::Cell::background,
	Resources::ActivityMenu::background;

std::unique_ptr<Date> Resources::DateCalendar::Cell::highlighted(nullptr);

bool Resources::load()
{
	return arial.loadFromFile("arial.ttf");
}

bool Resources::DateCalendar::loadBackground(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
{
	sf::Image i;
	i.create(width, height, backgroundColor);

	return background.loadFromImage(i);
}

bool Resources::DateCalendar::Cell::loadBackground(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
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
