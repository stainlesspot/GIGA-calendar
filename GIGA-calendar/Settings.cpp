#include "Settings.h"

Padding::Padding()
	: Padding(0)
{}

Padding::Padding(uint16_t all)
	: Padding(all, all, all, all)
{}

Padding::Padding(uint16_t topAndBottom, uint16_t rightAndLeft)
	: Padding(topAndBottom, rightAndLeft, topAndBottom, rightAndLeft)
{}

Padding::Padding(uint16_t top, uint16_t rightAndLeft, uint16_t bottom)
	: Padding(top, rightAndLeft, bottom, rightAndLeft)
{}

Padding::Padding(uint16_t top, uint16_t right, uint16_t bottom, uint16_t left)
	: top(top), right(right), bottom(bottom), left(left)
{}


const uint8_t Settings::DateCalendar::Cell::charSize(35);

const uint16_t Settings::DateCalendar::spaceBetweenCells(15),
	Settings::DateCalendar::spaceBetweenRows(10);

const Padding Settings::MainWindow::padding(1),
	Settings::DateCalendar::padding(100, 50);

const sf::Color Settings::MainWindow::backgroundColor(150, 150, 150, 255),
	Settings::DateCalendar::backgroundColor(255, 255, 255, 255),
	Settings::DateCalendar::Cell::textColor(255, 255, 255, 255),
	Settings::ActivityMenu::backgroundColor(40, 255, 40, 255);

const std::array<sf::Color, 13> Settings::DateCalendar::Cell::monthColors = {
	sf::Color(255, 255, 255, 255),		//	Base
	sf::Color(0, 255, 0, 255),			//	January 
	sf::Color(0, 255, 0, 255),			//	February
	sf::Color(0, 255, 0, 255),			//	March
	sf::Color(100, 100, 255, 255),		//	April
	sf::Color(100, 255, 100, 255),		//	May
	sf::Color(255, 100, 100, 255),		//	June
	sf::Color(0, 255, 0, 255),			//	July
	sf::Color(0, 255, 0, 255),			//	August
	sf::Color(0, 255, 0, 255),			//	September
	sf::Color(0, 255, 0, 255),			//	October
	sf::Color(0, 255, 0, 255),			//	Novermber
	sf::Color(0, 255, 0, 255)			//	December
};

/*const uint8_t Settings::MainWindow::padding(1),
	Settings::dateCalendarPadding(50),
	Settings::spaceBetweenCells(15),
	Settings::spaceBetweenRows(10),
	Settings::cellCharSize(35);

const sf::Color Settings::mainWindowBackgroundColor(150,150,150,255),
	Settings::dateCalendarBackgroundColor(255, 0, 0, 255),
	Settings::activityMenuBackgroundColor(40, 255, 40, 255),
	Settings::cellColor(0, 255, 0, 255),
	Settings::cellTextColor(255, 255, 255, 255);

std::array<sf::Color, 13> Settings::monthCellColors = {
	sf::Color(255, 255, 255, 255),		//	Base
	sf::Color(0, 255, 0, 255),			//	January 
	sf::Color(0, 255, 0, 255),			//	February
	sf::Color(0, 255, 0, 255),			//	March
	sf::Color(100, 100, 255, 255),		//	April
	sf::Color(100, 255, 100, 255),		//	May
	sf::Color(255, 100, 100, 255),		//	June
	sf::Color(0, 255, 0, 255),			//	July
	sf::Color(0, 255, 0, 255),			//	August
	sf::Color(0, 255, 0, 255),			//	September
	sf::Color(0, 255, 0, 255),			//	October
	sf::Color(0, 255, 0, 255),			//	Novermber
	sf::Color(0, 255, 0, 255)			//	December
};*/

