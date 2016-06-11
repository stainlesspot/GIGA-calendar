#pragma once

#include <SFML/Graphics.hpp>
#include <GUI/GUI.h>

#include "DateCalendar.h"
#include "ActivityMenu.h"
class MainWindow {
private:
	
	struct Calendar;

	struct Calendar {

		struct Cell {
			uint16_t width, height;
			
			sf::Vector2f position;

			gui::Button button;

			Date date;

			const gui::Button& generateButton();
			const gui::Button& updateButton();

			void operator--();
			void operator++();

		};

		uint16_t width, height;

		sf::View view;

		gui::Window window;

		uint8_t viewPosition;
		Cell first, last;

		void load(const bool beforeFirst, const uint16_t numberOfRows, const bool calibrate = false);
		void unload(const bool afterFirst, const uint16_t numberOfRows);

	};

	

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