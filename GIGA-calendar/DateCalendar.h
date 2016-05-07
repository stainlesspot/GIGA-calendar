#pragma once

#include <GUI/GUI.h>

class DateCalendar {
private:
	gui::Window* subWindow = nullptr;

public:
	DateCalendar(gui::WindowManager&);

	void prepare();
};