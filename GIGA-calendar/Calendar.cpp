#include "Calendar.h"

void Calendar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(main, states);
}

Calendar & Calendar::prepare()
{
	sf::Image greenImage;
	//greenImage.create();
	sf::Texture whiteTexture();
	main.emplace("dateCalendar", gui::Window(), true);
	return *this;
}
