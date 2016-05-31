#pragma once

#include <cstdint>
#include <array>

#include <SFML/Graphics.hpp>

struct Padding {
	uint16_t top, right, bottom, left;
	Padding();
	Padding(uint16_t all);
	Padding(uint16_t topAndBottom, uint16_t rightAndLeft);
	Padding(uint16_t top, uint16_t rightAndLeft, uint16_t bottom);
	Padding(uint16_t top, uint16_t right, uint16_t bottom, uint16_t left);
};

struct Settings {
	
	struct MainWindow {
		static const Padding padding;
		static const sf::Color backgroundColor;
	};

	struct DateCalendar {
		static const uint16_t spaceBetweenCells, spaceBetweenRows;
		static const Padding padding;
		static const sf::Color backgroundColor;

		struct MonthScroll {
			struct Previous {
				static const uint8_t rightMargin;
			};
			
			struct Next {
				static const uint8_t rightMargin;
			};

		};

		struct Cell {
			static const uint8_t charSize;
			static const sf::Color textColor;
			static const std::array<sf::Color, 13> monthColors;
		};
	};

	struct ActivityMenu {
		static const sf::Color backgroundColor;
	};

};