#pragma once

#include <cstdint>
#include <array>

#include <SFML/Graphics.hpp>

struct Settings {
	static const uint8_t mainWindowPadding, dateCalendarPadding, spaceBetweenCells, spaceBetweenRows, cellCharSize;
	static const sf::Color mainWindowBackgroundColor, dateCalendarBackgroundColor, activityMenuBackgroundColor, cellColor, cellTextColor;
	static std::array<sf::Color, 13> monthCellColors;
};