#include "Settings.h"
#include <fstream>

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



float Settings::Calendar::Cell::shaderDarkening(0.15f);


uint16_t
	Settings::MainWindow::width(sf::VideoMode::getDesktopMode().width),
	Settings::MainWindow::height(sf::VideoMode::getDesktopMode().height),

	Settings::Calendar::preemptiveMonthLoad(1),
	Settings::Calendar::spaceBetweenCells(1),
	Settings::Calendar::spaceBetweenRows(1),
	Settings::Calendar::numberOfRows(6),
	Settings::Calendar::Cell::characterSize(35),
	Settings::Calendar::MonthLabel::characterSize(30),
	Settings::Calendar::MonthScroll::Next::rightMargin(0),
	Settings::Calendar::MonthScroll::Next::bottomMargin(30),
	Settings::Calendar::MonthScroll::Previous::rightMargin(15),
	Settings::Calendar::MonthScroll::Previous::bottomMargin(30),
	
	Settings::ActivityMenu::EventNode::characterSize(15),
	Settings::ActivityMenu::EventNode::spaceBetweenRows(5),
	Settings::ActivityMenu::EventNode::numberOfRows(12),
	Settings::ActivityMenu::EventNode::hourMarginLeft(10),
	Settings::ActivityMenu::HighlightedDateMsg::marginTop(10),
	Settings::ActivityMenu::HighlightedDateMsg::marginBottom(10);



Spacing
	Settings::MonthView::margin(0, 0),
	Settings::MainWindow::padding(1),
	Settings::Calendar::margin(100, 50),
	Settings::Calendar::Cell::padding(10),
	Settings::Calendar::MonthLabel::margin(30, 10),
	Settings::ActivityMenu::EventNode::margin(50, 50, 10);



sf::Color
	Settings::MainWindow::backgroundColor(150, 150, 150, 255),
	Settings::Calendar::backgroundColor(255, 255, 255, 255),
	Settings::Calendar::Cell::textColor(255, 255, 255, 255),
	Settings::ActivityMenu::backgroundColor(62, 230, 123, 255),
	Settings::ActivityMenu::EventNode::backgroundColor(255, 255, 255, 255);



std::array<sf::Color, 13> Settings::Calendar::Cell::monthColors = {
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
	sf::Color(220, 41, 66, 255),			//	November
	sf::Color(47, 130, 146, 255)			//	December
};


void Settings::loadFromFile(const std::string & filename)
{

	std::unordered_map<std::string, float*> floats;
	std::unordered_map<std::string, uint16_t*> integers;
	std::unordered_map<std::string, Spacing*> spacings;
	std::unordered_map<std::string, sf::Color*> colors;


	floats.insert(std::pair<std::string, float*>("Calendar::Cell::shaderDarkening", &Calendar::Cell::shaderDarkening));


	integers = {
		std::pair<std::string, uint16_t*>("Calendar::preemptiveMonthLoad", &Calendar::preemptiveMonthLoad),
		std::pair<std::string, uint16_t*>("Calendar::Cell::characterSize", &Calendar::Cell::characterSize),
		std::pair<std::string, uint16_t*>("Calendar::MonthScroll::Previous::rightMargin", &Calendar::MonthScroll::Previous::rightMargin),
		std::pair<std::string, uint16_t*>("Calendar::MonthScroll::Previous::bottomMargin", &Calendar::MonthScroll::Previous::bottomMargin),
		std::pair<std::string, uint16_t*>("Calendar::MonthScroll::Next::rightMargin", &Calendar::MonthScroll::Next::rightMargin),
		std::pair<std::string, uint16_t*>("Calendar::MonthScroll::Next::bottomMargin", &Calendar::MonthScroll::Next::bottomMargin),
		std::pair<std::string, uint16_t*>("ActivityMenu::HighlightedDateMsg::marginTop", &ActivityMenu::HighlightedDateMsg::marginTop),
		std::pair<std::string, uint16_t*>("MainWindow::width", &MainWindow::width),
		std::pair<std::string, uint16_t*>("MainWindow::height", &MainWindow::height),
		std::pair<std::string, uint16_t*>("Calendar::spaceBetweenCells", &Calendar::spaceBetweenCells),
		std::pair<std::string, uint16_t*>("Calendar::spaceBetweenRows", &Calendar::spaceBetweenRows),
		std::pair<std::string, uint16_t*>("Calendar::numberOfRows", &Calendar::numberOfRows)
	};


	spacings = {
		std::pair<std::string, Spacing*>("MonthView::margin", &MonthView::margin),
		std::pair<std::string, Spacing*>("MainWindow::padding", &MainWindow::padding),
		std::pair<std::string, Spacing*>("Calendar::margin", &Calendar::margin)
	};


	colors = { 
		std::pair<std::string, sf::Color*>("MainWindow::backgroundColor", &MainWindow::backgroundColor),
		std::pair<std::string, sf::Color*>("Calendar::backgroundColor", &Calendar::backgroundColor),
		std::pair<std::string, sf::Color*>("Calendar::Cell::textColor", &Calendar::Cell::textColor),
		std::pair<std::string, sf::Color*>("ActivityMenu::backgroundColor", &ActivityMenu::backgroundColor),

		std::pair<std::string, sf::Color*>("Calendar::Cell::januaryColor", &Calendar::Cell::monthColors[1]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::jebruaryColor", &Calendar::Cell::monthColors[2]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::marchColor", &Calendar::Cell::monthColors[3]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::aprilColor", &Calendar::Cell::monthColors[4]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::mayColor", &Calendar::Cell::monthColors[5]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::juneColor", &Calendar::Cell::monthColors[6]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::julyColor", &Calendar::Cell::monthColors[7]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::augustColor", &Calendar::Cell::monthColors[8]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::septemberColor", &Calendar::Cell::monthColors[9]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::octoberColor", &Calendar::Cell::monthColors[10]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::novemberColor", &Calendar::Cell::monthColors[11]),
		std::pair<std::string, sf::Color*>("Calendar::Cell::decemberColor", &Calendar::Cell::monthColors[12])
	};



	std::ifstream reader(filename, std::ios::in);

	if (reader) {
		std::string line, structName, variableName, value;
		size_t structStart, assignmentPosition;


		while (!reader.eof()) {
			std::getline(reader, line);

			line = line.substr(0, line.find('#'));

			structStart = line.find('{');
			if (structStart != std::string::npos) {

				structName = removeWhiteSpaces(line.substr(0, structStart - 1));
				structName += "::";

				while (line.find('}') == std::string::npos) {
					std::getline(reader, line);

					line = line.substr(0, line.find('#'));

					assignmentPosition = line.find('=');

					if (assignmentPosition != std::string::npos) {
						variableName = structName + removeWhiteSpaces(line.substr(0, assignmentPosition));
						value = removeWhiteSpaces(line.substr(assignmentPosition + 1));

						if (floats.find(variableName) != floats.end()) {
							*floats[variableName] = std::stof(value);
						}
						else if (integers.find(variableName) != integers.end()) {
							*integers[variableName] = std::stoi(value);
						}
						else if (spacings.find(variableName) != spacings.end()) {
							*spacings[variableName] = stringToSpacing(value);
						}
						else if (colors.find(variableName) != colors.end()) {
							*colors[variableName] = stringToColor(value);
						}

					}
				}

			}
		}
		reader.close();
	}
}

std::string Settings::removeWhiteSpaces(std::string string) {
	string.erase(std::remove_if(string.begin(), string.end(), ::isspace), string.end());
	return string;
}

Spacing Settings::stringToSpacing(const std::string& string) {
	size_t firstOcc = string.find(','), secondsOcc = string.find(',', firstOcc + 1), thirdOcc = string.find(',', secondsOcc + 1);
	switch(std::count(string.begin(), string.end(), ',')) {
		case 0:
			return Spacing(std::stoi(string));
		case 1:
			return Spacing(std::stoi(string.substr(0, firstOcc)), std::stoi(string.substr(firstOcc)));
		case 2:
			return Spacing(std::stoi(string.substr(0, firstOcc)), std::stoi(string.substr(firstOcc, secondsOcc)), std::stoi(string.substr(secondsOcc)));
		case 3:
			return Spacing(std::stoi(string.substr(0, firstOcc)), std::stoi(string.substr(firstOcc, secondsOcc)), std::stoi(string.substr(secondsOcc, thirdOcc)), std::stoi(string.substr(thirdOcc)));
	}

}
sf::Color Settings::stringToColor(const std::string& string) {
	if (string[0] == '(') {
		size_t firstOcc = string.find(','), secondsOcc = string.find(',', firstOcc + 1), thirdOcc = string.find(',', secondsOcc + 1);
		return sf::Color(std::stoi(string.substr(0, firstOcc)), std::stoi(string.substr(firstOcc, secondsOcc)), std::stoi(string.substr(secondsOcc, thirdOcc)), std::stoi(string.substr(thirdOcc)));
	}
}