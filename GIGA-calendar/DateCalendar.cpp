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

void DateCalendar::prepare()
{
	//std::cout << "Date : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << "]}" << std::endl;


	Resources::loadBackground(width, height, Settings::backgroundColor);

	setBackgroundTexture(Resources::background);

	Resources::MonthScroll::Previous::loadBackground();

	add("previousMonthButton", gui::Button().setTexture(Resources::MonthScroll::Previous::background)
		.setPosition(width - ));


	Date date(Date::now().setDay(1));
	
	generateRows(date - date.getDayOfWeek());

	
}

void DateCalendar::generateRows(Date date)
{
	const auto cellHeight = (height - Settings::padding.top - Settings::padding.bottom - 5 * Settings::spaceBetweenRows) / 6,
		cellWidth = (width - Settings::padding.left - Settings::padding.right - 6 * Settings::spaceBetweenCells) / 7;

	Resources::Cell::loadBackground(cellWidth, cellHeight);

	for (uint8_t row = 0; row < 6; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {
			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Cell::charSize);

			add("row" + std::to_string(row) + ": cell" + std::to_string(cell), gui::Button().setTexture(Resources::Cell::background)
				.setPosition((cellWidth + Settings::spaceBetweenCells) * cell + Settings::padding.left,
				(cellHeight + Settings::spaceBetweenRows) * row + Settings::padding.top)
				.setName(text.setColor(Settings::Cell::textColor).setPosition((text.getGlobalBounds().width - cellWidth) / 2 + 8, (text.getGlobalBounds().height - cellHeight / 2)))
				.setColor(Settings::Cell::monthColors[date.getMonth()])
				.bindAction(gui::Event::Released, [date]() {
					Resources::Cell::highlighted.reset(new Date(date));
				}));

			date = date + 1;
		}
}
