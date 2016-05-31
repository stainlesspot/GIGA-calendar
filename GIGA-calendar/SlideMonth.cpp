#include "SlideMonth.h"


void SlideMonth::step() const
{
	if (!upwards) {
		gui::Interactive* currentCell;
		for (uint8_t row = 0; row < 6; row++)
			for (uint8_t cell = 0; cell < 7; cell++) {
				currentCell = &window.at("row" + std::to_string(row) + ": cell" + std::to_string(cell));
				currentCell->setPosition(currentCell->getPosition() + sf::Vector2f(0, 10));
			}
	}
}

SlideMonth::SlideMonth(bool upwards, gui::Window & window)
	: upwards(upwards), window(window)
{}
