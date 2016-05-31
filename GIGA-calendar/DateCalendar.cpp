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

void DateCalendar::prepare(sf::View& view)
{
	//std::cout << "Date : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << "]}" << std::endl;


	R::loadBackground(width, height, S::backgroundColor);

	setBackgroundTexture(R::background);


	R::MonthScroll::Next::loadBackground();
	
	unsigned int nextmbX = width - S::MonthScroll::Next::rightMargin - R::MonthScroll::Next::background.getSize().x - S::padding.right;

	add("nextMonth", gui::Button().setTexture(R::MonthScroll::Next::background)
		.setPosition(nextmbX, S::padding.top - S::MonthScroll::Next::bottomMargin - R::MonthScroll::Next::background.getSize().y)
		/*.bindAction(gui::Event::Released, [this]() {
			((gui::Button&)(this->at("row1: cell1"))).;
			this->erase
		})*/);
	
	
	R::MonthScroll::Previous::loadBackground();

	add("previousMonth", gui::Button().setTexture(R::MonthScroll::Previous::background)
		.setPosition(nextmbX - S::MonthScroll::Previous::rightMargin - R::MonthScroll::Previous::background.getSize().x,
			S::padding.top - S::MonthScroll::Previous::bottomMargin - R::MonthScroll::Previous::background.getSize().y));


	/*const unsigned int viewWidth = width - S::padding.left - S::padding.right + Settings::View::padding.left + Settings::View::padding.right,
		viewHeight = height - S::padding.top - S::padding.bottom + Settings::View::padding.top + Settings::View::padding.bottom,
		viewX = viewWidth / 2 + S::padding.left + Settings::MainWindow::padding.left - Settings::View::padding.left,
		viewY = viewHeight + S::padding.top + Settings::MainWindow::padding.top - Settings::View::padding.top;

	view.setSize(viewWidth, viewHeight);
	view.setCenter(viewX, viewY);
	view.setViewport(sf::FloatRect(viewX, viewY, 1, 1));
*/	
	Date date(Date::now().setDay(1));
	
	date = date - date.getDayOfWeek();

	const auto cellHeight = (height - S::padding.top - S::padding.bottom - 5 * S::spaceBetweenRows) / 6,
		cellWidth = (width - S::padding.left - S::padding.right - 6 * S::spaceBetweenCells) / 7;

	const uint8_t widthLoss((width - S::padding.left - S::padding.right - 6 * S::spaceBetweenCells) % 7);



	R::Cell::loadBackground(cellWidth, cellHeight);

	for (uint8_t row = 0; row < 6; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {
			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, S::Cell::charSize);

			add("row" + std::to_string(row) + ": cell" + std::to_string(cell), gui::Button().setTexture(R::Cell::background)
				.setPosition((cellWidth + S::spaceBetweenCells) * cell + S::padding.left + ((widthLoss > cell) ? (cell - widthLoss) : widthLoss),
					(cellHeight + S::spaceBetweenRows) * row + S::padding.top)
				.setName(text.setColor(S::Cell::textColor).setPosition((text.getGlobalBounds().width - cellWidth) / 2 + 8, (text.getGlobalBounds().height - cellHeight / 2)))
				.setColor(S::Cell::monthColors[date.getMonth()])
				.bindAction(gui::Event::Released, [date]() {
				R::Cell::highlighted.reset(new Date(date));
			}));

			date = date + 1;
		}
	
}

/*void DateCalendar::generateRows(Date date)
{
	const auto cellHeight = (height - S::padding.top - S::padding.bottom - 5 * S::spaceBetweenRows) / 6,
		cellWidth = (width - S::padding.left - S::padding.right - 6 * S::spaceBetweenCells) / 7;

	const uint8_t widthLoss((width - S::padding.left - S::padding.right - 6 * S::spaceBetweenCells) % 7);


	R::Cell::loadBackground(cellWidth, cellHeight);

	for (uint8_t row = 0; row < 6; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {
			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, S::Cell::charSize);

			add("row" + std::to_string(row) + ": cell" + std::to_string(cell), gui::Button().setTexture(R::Cell::background)
				.setPosition((cellWidth + S::spaceBetweenCells) * cell + S::padding.left + ((widthLoss > cell) ? (cell - widthLoss) : widthLoss),
				(cellHeight + S::spaceBetweenRows) * row + S::padding.top)
				.setName(text.setColor(S::Cell::textColor).setPosition((text.getGlobalBounds().width - cellWidth) / 2 + 8, (text.getGlobalBounds().height - cellHeight / 2)))
				.setColor(S::Cell::monthColors[date.getMonth()])
				.bindAction(gui::Event::Released, [date]() {
					R::Cell::highlighted.reset(new Date(date));
				}));

			date = date + 1;
		}
}*/
