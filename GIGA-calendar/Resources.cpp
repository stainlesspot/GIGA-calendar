#include "Resources.h"
#include <memory>

sf::Font Resources::arial;

sf::Texture
	Resources::Calendar::background,
	Resources::Calendar::Cell::background,
	Resources::Calendar::MonthScroll::Previous::background,
	Resources::Calendar::MonthScroll::Next::background,
	Resources::ActivityMenu::background,
	Resources::ActivityMenu::EventWindow::background;


std::unique_ptr<Date> Resources::Calendar::Cell::highlighted(nullptr);

bool Resources::load()
{
	return arial.loadFromFile("resources/arial.ttf");
}

bool Resources::load(sf::Texture & texture, const std::string& filepath)
{
	return texture.loadFromFile(filepath);
}

bool Resources::load(sf::Texture& texture, const uint16_t width, const uint16_t height, const sf::Color & color)
{	
	sf::Image i;
	i.create(width, height, color);

	return texture.loadFromImage(i);
}
