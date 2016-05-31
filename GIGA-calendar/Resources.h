#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Date.h"

struct Resources {
	static sf::Font arial;

	static bool load();

	struct DateCalendar {
		static sf::Texture background;

		static bool loadBackground(const uint16_t width, const uint16_t height, const sf::Color& backgroundColor = sf::Color::White);

		struct MonthScroll {
			struct Previous {
				static sf::Texture background;

				static bool loadBackground();
			};

			struct Next {
				static sf::Texture background;

				static bool loadBackground();
			};
		};

		struct Cell {
			static std::unique_ptr<Date> highlighted;

			static sf::Texture background;

			static bool loadBackground(const uint16_t width, const uint16_t height, const sf::Color& backgroundColor = sf::Color::White);
		};
	};

	struct ActivityMenu {
		static sf::Texture background;

		static bool loadBackground(const uint16_t width, const uint16_t height, const sf::Color& backgroundColor = sf::Color::White);
	};

};