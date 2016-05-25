#include "Settings.h"

const uint8_t Settings::mainWindowPadding(1),
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
};
