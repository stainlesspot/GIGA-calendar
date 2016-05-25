#pragma once

#include <array>

#include <GUI/Button.h>

#include "Cell.h"

//	A row represents a week in the calendar and thus is made up of seven cells,
//	each with ascending dates. The row is used in scrolling the calendar,
//	in order to move the cells together. The row with the currently selected
//	cell is also highlighted
class Row : public sf::Drawable{
private:
	std::array<gui::Button, 7> week;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Row(const sf::Vector2f position, const uint16_t width, const uint16_t height, const Date& date, const std::array<gui::Button, 7>& week);

	Row() = default;
	Row(const Row&) = default;
	Row(Row&&) = default;
	~Row() = default;


	Row& setHeight(const float);

	Row& move(const float height);

	Row& operator =(const Row&) = default;
	Row& operator =(Row&&) = default;

};