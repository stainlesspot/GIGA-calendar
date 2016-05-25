#include "DateCalendar.h"
#include "Settings.h"
#include "Resources.h"
#include <iostream>

void DateCalendar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	gui::Window::draw(target, states);

	for (auto it(calendar.begin()), end(calendar.end()); it != end; it++)
		target.draw(*it, states);

}

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
	sf::Image backgroundImage;
	backgroundImage.create(width, height, Settings::dateCalendarBackgroundColor);
	
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromImage(backgroundImage);

	setBackgroundTexture(backgroundTexture);


	//calendar.push_back(Row(sf::Vector2f(Settings::dateCalendarPadding, Settings::dateCalendarPadding), rowWidth, rowHeight, Date::now().setDay(1)));

	const auto rowWidth = width - 2 * Settings::dateCalendarPadding, rowHeight = (height - 2 * Settings::dateCalendarPadding - 5 * Settings::spaceBetweenRows) / 6,
	cellWidth = (rowWidth - 6 * Settings::spaceBetweenCells) / 7;

	Date date(Date::now().setDay(1));
	

	//std::cout << "Date : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << "]}" << std::endl;

	
	date = date - date.getDayOfWeek();

//	std::cout << "Date2 : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << "]}" << std::endl;

	Resources::loadCalendarCell(cellWidth, rowHeight);

	for (uint8_t row = 0; row < 6; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {
	//		std::cout << "Day: " << int(date.getDay()) << ", Month: " << int(date.getMonth()) << std::endl;
			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::cellCharSize);
			add("row" + std::to_string(row) + ": cell" + std::to_string(cell), gui::Button().setTexture(Resources::calendarCell)
				.setPosition((cellWidth + Settings::spaceBetweenCells) * cell + Settings::dateCalendarPadding, (rowHeight + Settings::spaceBetweenRows) * row + Settings::dateCalendarPadding)
				.setName(text.setColor(Settings::cellTextColor).setPosition( text.getGlobalBounds().width / 2 - cellWidth / 2 + 8, text.getGlobalBounds().height / 2 - rowHeight / 2))
				.setColor(Settings::monthCellColors[date.getMonth()]));

			date = date + 1;

		}
	
	return *this;
}
