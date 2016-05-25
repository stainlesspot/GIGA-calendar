#pragma once

#include <GUI/Window.h>
#include <deque>

#include "Row.h"

class DateCalendar : public gui::Window {
private:
	unsigned int width;
	unsigned int height;

	std::deque<Row> calendar;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	DateCalendar(const sf::Vector2f& position, const unsigned int width, const unsigned int height, const bool isMovable = false);

	DateCalendar() = default;
	DateCalendar(const DateCalendar&) = default;
	DateCalendar(DateCalendar&&) = default;
	~DateCalendar() = default;

	std::unique_ptr<gui::Window> copy() const override;
	std::unique_ptr<gui::Window> move() override;

//	const bool input(const sf::Event& event);

	DateCalendar& prepare();

	DateCalendar& operator =(const DateCalendar&) = default;
	DateCalendar& operator =(DateCalendar&&) = default;

};