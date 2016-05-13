#include "DateCalendar.h"
 

DateCalendar::DateCalendar(const sf::Vector2f& position, const unsigned int width, const unsigned int height,
	const sf::Color& backgroundTextureColor, bool isMovable = false)
	: width(width), height(height), backgroundTextureColor(backgroundTextureColor)
{
	setPosition(position);
	setMovable(isMovable);
}

/*
const bool DateCalendar::input(const sf::Event & event)
{
	switch (event.type) {
	case sf::Event::MouseWheelScrolled:
		event.mouseWheelScroll.wheel
	}
	return false;
}*/

DateCalendar& DateCalendar::prepare()
{
	sf::Image backgroundImage;
	backgroundImage.create(width, height, backgroundTextureColor);
	
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromImage(backgroundImage);

	setBackgroundTexture(backgroundTexture);


	return *this;
}
