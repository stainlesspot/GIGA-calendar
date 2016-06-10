#pragma once

#include <cstdint>
#include <array>

#include <SFML/Graphics.hpp>

struct Spacing {
	uint16_t top, right, bottom, left;
	Spacing();
	Spacing(uint16_t all);
	Spacing(uint16_t topAndBottom, uint16_t rightAndLeft);
	Spacing(uint16_t top, uint16_t rightAndLeft, uint16_t bottom);
	Spacing(uint16_t top, uint16_t right, uint16_t bottom, uint16_t left);
};

struct Settings {
	
	struct MonthView {
		static const Spacing margin;
	};

	struct MainWindow {
		static const uint16_t width, height;
		static const Spacing padding;
		static const sf::Color backgroundColor;
	};

	struct Calendar {
		static const uint8_t preemtiveMonthLoad;
		static const uint16_t spaceBetweenCells, spaceBetweenRows, scrollDistance;
		static const Spacing margin;
		static const sf::Color backgroundColor;

		struct MonthScroll {
			struct Previous {
				static const uint8_t rightMargin, bottomMargin;
			};
			
			struct Next {
				static const uint8_t rightMargin, bottomMargin;
			};

		};

		struct Cell {
			static const float shaderDarkening;
			static const uint8_t charSize;
			static const sf::Color textColor;
			static const std::array<sf::Color, 13> monthColors;
		};
	};

	struct ActivityMenu {
		static const sf::Color backgroundColor;
	};

};