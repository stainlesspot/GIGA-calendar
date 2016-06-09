#pragma once

#include <SFML/Graphics.hpp>
#include <GUI/GUI.h>

#include "DateCalendar.h"
#include "ActivityMenu.h"
class MainWindow {
private:
	
	struct Calendar;

	unsigned int width;
	unsigned int height;

	Calendar calendar;

	gui::Window calendarHUD;
//	gui::Window dateCalendar;

	gui::Window activityMenu;

	gui::WindowManager windowManager;


	

public:
	MainWindow();

	void loadFrom(const std::string& filename);
	void saveTo(const std::string& filename);

//	void prepare();
	void initialize();

};