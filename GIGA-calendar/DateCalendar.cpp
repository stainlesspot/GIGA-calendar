#include <iostream>

#include <GUI\GUI.h>

#include "DateCalendar.h"
#include "Settings.h"
#include "Resources.h"
#include "Date.h"



DateCalendar::DateCalendar(const sf::Vector2f& position, const unsigned int width, const unsigned int height, const bool isMovable)
	: width(width), height(height)
{
	setPosition(position);
	setMovable(isMovable);
}


/*const bool DateCalendar::input(const sf::Event & event)
{
/*	switch (event.type) {
	case sf::Event::MouseWheelScrolled:
		event.mouseWheelScroll.wheel
	}
	return false;
}*/

std::unique_ptr<gui::Window> DateCalendar::copy() const
{
	return std::unique_ptr<gui::Window>(new DateCalendar(*this));
}

std::unique_ptr<gui::Window> DateCalendar::move()
{
	return std::unique_ptr<gui::Window>(new DateCalendar(std::move(*this)));
}

DateCalendar& DateCalendar::prepare()
{
	
	Resources::DateCalendar::loadBackground(width, height, Settings::DateCalendar::backgroundColor);

	setBackgroundTexture(Resources::DateCalendar::background);


	
	const auto cellHeight = (height - Settings::DateCalendar::padding.top - Settings::DateCalendar::padding.bottom - 5 * Settings::DateCalendar::spaceBetweenRows) / 6,
	cellWidth = (width - Settings::DateCalendar::padding.left - Settings::DateCalendar::padding.right - 6 * Settings::DateCalendar::spaceBetweenCells) / 7;

	Date date(Date::now().setDay(1));
	

	//std::cout << "Date : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << "]}" << std::endl;

	
	date = date - date.getDayOfWeek();

	Resources::DateCalendar::Cell::loadBackground(cellWidth, cellHeight);

	for (uint8_t row = 0; row < 6; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {
			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::DateCalendar::Cell::charSize);

			add("row" + std::to_string(row) + ": cell" + std::to_string(cell), gui::Button().setTexture(Resources::DateCalendar::Cell::background)
				.setPosition((cellWidth + Settings::DateCalendar::spaceBetweenCells) * cell + Settings::DateCalendar::padding.left,
					(cellHeight + Settings::DateCalendar::spaceBetweenRows) * row + Settings::DateCalendar::padding.top)
				.setName(text.setColor(Settings::DateCalendar::Cell::textColor).setPosition((text.getGlobalBounds().width - cellWidth) / 2 + 8, (text.getGlobalBounds().height - cellHeight / 2)))
				.setColor(Settings::DateCalendar::Cell::monthColors[date.getMonth()])
				.bindAction(gui::Event::Released, [date]() {
					Resources::DateCalendar::Cell::highlighted.reset(new Date(date));
				})
				);

			date = date + 1;
		}
	return *this;
}
