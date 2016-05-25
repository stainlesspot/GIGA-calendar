#pragma once

#include <SFML/Graphics.hpp>
#include <GUI/GUI.h>

#include "DateCalendar.h"
#include "ActivityMenu.h"
class MainWindow {
private:

	unsigned int width;
	unsigned int height;

	gui::WindowManager windowManager;
	DateCalendar leftSide;
	ActivityMenu rightSide;


public:
	MainWindow();

	void loadFrom(const std::string& filename);
	void saveTo(const std::string& filename);

	void prepare();
	void initialize();

};