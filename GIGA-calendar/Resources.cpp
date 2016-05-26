#include "Resources.h"

sf::Font Resources::arial;
sf::Texture Resources::DateCalendar::background,
	Resources::DateCalendar::Cell::background;


void Resources::load()
{
	arial.loadFromFile("arial.ttf");
}

void Resources::DateCalendar::load(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
{
	sf::Image i;
	i.create(width, height, backgroundColor);

	background.loadFromImage(i);
}

void Resources::DateCalendar::Cell::load(const uint16_t width, const uint16_t height, const sf::Color & backgroundColor)
{
	sf::Image i;
	i.create(width, height, backgroundColor);

	background.loadFromImage(i);
}
