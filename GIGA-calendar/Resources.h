#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Date.h"

struct Resources {
	static sf::Font arial;

	static bool load();
	static bool load(sf::Texture& texture, const std::string& filepath);
	static bool load(sf::Texture& texture, const uint16_t width, const uint16_t height, const sf::Color& color);

	struct Calendar {
		static sf::Texture background;

		struct MonthScroll {
			struct Previous {
				static sf::Texture background;
			};

			struct Next {
				static sf::Texture background;
			};
		};

		struct Cell {
			static std::unique_ptr<Date> highlighted;

			static sf::Texture background;
		};
	};

	struct ActivityMenu {
		static sf::Texture background;

		struct EventNode {
			static sf::Texture background;
		};
	};

};