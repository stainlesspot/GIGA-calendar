#pragma once

#include <SFML/Graphics.hpp>
#include <GUI/GUI.h>

#include "DateCalendar.h"
#include "ActivityMenu.h"
class MainWindow {
private:

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

		Date viewPosition, start;
		sf::View view;

		gui::Window window, hud;

		Cell first, last;

		void move(const int16_t rows);

		void load(const bool beforeFirst, const uint16_t numberOfRows, const bool calibrate = false);
		void unload(const bool afterFirst, const uint16_t numberOfRows);

	};


	Calendar calendar;

	gui::Window activityMenu;

	gui::WindowManager windowManager;


	

public:
	void loadFrom(const std::string& filename);
	void saveTo(const std::string& filename);

	void initialize();

};