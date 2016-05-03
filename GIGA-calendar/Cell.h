#pragma once
#include "Event.h"
#include "Task.h"
#include <vector>
#include <SFML/Graphics.hpp>

//	Visually the calendar is made up of colored rectangles, or cells,
//	each representing a concrete date. They follow an ascending order.
//	Each row represents a week and so each column represents a day of the week.
//	Every cell of a given month has the same color and neighbouring months
//	have different color schemes in order to be easily differentiated.
//	Weekends and holydays have a different shade of the month's color
//	from regular working days. The present day also has a distinct color.
//	Clicking on a cell highlights (selects) her, and brings upon the event menu.
//	There can only be one selected cell. 
//	On default the present day is selected.
class Cell {

private:
	Point position;
	sf::RectangleShape shape;
	Date date;
	std::vector<Activity> activities;

public:
	Cell();
	Cell(const Date&, const std::vector<Activity>& v = std::vector<Activity>(0));
	Cell(const Cell&);
	
	Cell& setPosition(const Point&);
	Cell& setShape(const sf::RectangleShape&);
	
};