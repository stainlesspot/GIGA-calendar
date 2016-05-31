#pragma once

#include <GUI/Window.h>
#include <deque>

#include "Settings.h"
#include "Resources.h"



class DateCalendar : public gui::Window {

	typedef Settings::DateCalendar(S);
	typedef Resources::DateCalendar(R);

private:
	unsigned int width;
	unsigned int height;

public:
	DateCalendar(const sf::Vector2f& position, const unsigned int width, const unsigned int height, const bool isMovable = false);

	DateCalendar() = default;
	DateCalendar(const DateCalendar&) = default;
	DateCalendar(DateCalendar&&) = default;
	~DateCalendar() = default;

	std::unique_ptr<gui::Window> copy() const override;
	std::unique_ptr<gui::Window> move() override;


	void prepare(sf::View&);

//	void generateRows(Date);

	DateCalendar& operator =(const DateCalendar&) = default;
	DateCalendar& operator =(DateCalendar&&) = default;

};