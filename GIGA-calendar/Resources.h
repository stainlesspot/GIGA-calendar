#pragma once

#include <SFML/Graphics.hpp>

struct Resources {
	static sf::Font arial;

	static void load();

	struct DateCalendar {
		
		static sf::Texture background;

		static void load(const uint16_t width, const uint16_t height, const sf::Color& backgroundColor = sf::Color::White);

		struct Cell {
			static sf::Texture background;

			static void load(const uint16_t width, const uint16_t height, const sf::Color& backgroundColor = sf::Color::White);
		};
	};

};