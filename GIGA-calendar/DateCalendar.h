#pragma once

#include <GUI/Window.h>
#include <deque>

#include "Row.h"

class DateCalendar : private gui::Window {
private:
	unsigned int width;
	unsigned int height;

	sf::Color backgroundTextureColor;

	std::deque<Row> calendar;

public:
	DateCalendar() = default;
	DateCalendar(const sf::Vector2f& position, const unsigned int width, const unsigned int height,
		const sf::Color& backgroundTextureColor, const bool isMovable = false);
	~DateCalendar() = default;

	const bool input(const sf::Event& event);

	DateCalendar& prepare();
};