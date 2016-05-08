#pragma once

#include <GUI/GUI.h>
#include <deque>

#include "Row.h"

class DateCalendar {
private:
	gui::Window* subWindow = nullptr;
	
	std::deque<Row> calendar;

public:
	DateCalendar() = default;
	DateCalendar(gui::Window&);

	DateCalendar& setSubWindow(gui::Window&);

	void prepare();
};