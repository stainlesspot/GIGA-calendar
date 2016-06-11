#include "Settings.h"

Spacing::Spacing()
	: Spacing(0)
{}

Spacing::Spacing(uint16_t all)
	: Spacing(all, all, all, all)
{}

Spacing::Spacing(uint16_t topAndBottom, uint16_t rightAndLeft)
	: Spacing(topAndBottom, rightAndLeft, topAndBottom, rightAndLeft)
{}

Spacing::Spacing(uint16_t top, uint16_t rightAndLeft, uint16_t bottom)
	: Spacing(top, rightAndLeft, bottom, rightAndLeft)
{}

Spacing::Spacing(uint16_t top, uint16_t right, uint16_t bottom, uint16_t left)
	: top(top), right(right), bottom(bottom), left(left)
{}

const float Settings::Calendar::Cell::shaderDarkening(0.15f);

const uint8_t Settings::Calendar::preemtiveMonthLoad(1),
	Settings::Calendar::Cell::charSize(35),
	Settings::Calendar::MonthScroll::Previous::rightMargin(15),
	Settings::Calendar::MonthScroll::Previous::bottomMargin(30),
	Settings::Calendar::MonthScroll::Next::rightMargin(0),
	Settings::Calendar::MonthScroll::Next::bottomMargin(30);

const uint16_t Settings::MainWindow::width(1280),
	Settings::MainWindow::height(720),
	Settings::Calendar::spaceBetweenCells(1),
	Settings::Calendar::spaceBetweenRows(1),
	Settings::Calendar::scrollDistance(20);

const Spacing Settings::MonthView::margin(15, 0),
	Settings::MainWindow::padding(1),
	Settings::Calendar::margin(100, 50);

const sf::Color Settings::MainWindow::backgroundColor(150, 150, 150, 255),
	Settings::Calendar::backgroundColor(255, 255, 255, 255),
	Settings::Calendar::Cell::textColor(255, 255, 255, 255),
	Settings::ActivityMenu::backgroundColor(62, 230, 123, 255);


const std::array<sf::Color, 13> Settings::Calendar::Cell::monthColors = {
	sf::Color(255, 255, 255, 255),			//	Base
	sf::Color(204, 153, 102, 255),			//	January 
	sf::Color(198, 175, 181, 255),			//	February
	sf::Color(191, 233, 227, 255),			//	March
	sf::Color(224, 73, 81, 220),			//	April
	sf::Color(123, 182, 97, 220),			//	May
	sf::Color(255, 216, 88, 220),			//	June
	sf::Color(230, 178, 184, 255),			//	July
	sf::Color(243, 130, 53, 255),			//	August
	sf::Color(89, 104, 174, 255),			//	September
	sf::Color(152, 180, 212, 255),			//	October
	sf::Color(220, 41, 66, 255),			//	Novermber
	sf::Color(47, 130, 146, 255)			//	December
};