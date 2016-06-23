#pragma once

#include <cstdint>
#include <array>
#include <unordered_map>

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
		static Spacing margin;
	};

	struct MainWindow {
		static uint16_t width, height;
		static Spacing padding;
		static sf::Color backgroundColor;
	};

	struct Calendar {
		static uint16_t preemptiveMonthLoad, spaceBetweenCells, spaceBetweenRows, numberOfRows;
		static Spacing margin;
		static sf::Color backgroundColor;

		struct MonthScroll {
			struct Previous {
				static uint16_t rightMargin, bottomMargin;
			};
			
			struct Next {
				static uint16_t rightMargin, bottomMargin;
			};

		};

		struct MonthLabel {
			static uint16_t characterSize;
			static Spacing margin;
		};

		struct Cell {
			static float shaderDarkening;
			static uint16_t characterSize;
			static Spacing padding;
			static sf::Color textColor;
			static std::array<sf::Color, 13> monthColors;
		};
	};

	struct ActivityMenu {

		struct HighlightedDateMsg {
			static uint16_t marginTop, marginBottom;
		};

		struct EventNode {
			static uint16_t characterSize, spaceBetweenRows, numberOfRows, hourMarginLeft;
			static Spacing margin;
			static sf::Color backgroundColor;
		};


		static sf::Color backgroundColor;
	};

	static void loadFromFile(const std::string& filename);

private:
	static std::string removeWhiteSpaces(std::string string);
	static Spacing stringToSpacing(const std::string& string);
	static sf::Color stringToColor(const std::string& string);
};