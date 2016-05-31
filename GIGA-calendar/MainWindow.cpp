
#include <iostream>

#include "MainWindow.h"
#include "Settings.h"
#include "Resources.h"
#include "SlideMonth.h"

MainWindow::MainWindow()
	: width(Settings::MainWindow::width), height(Settings::MainWindow::height),
	dateCalendar(sf::Vector2f(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top), width * 2 / 3 + ((width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.left,
		height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom)
{
	auto amWidth(width / 3 + ((width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.right),
		amHeight(height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom);

	Resources::ActivityMenu::loadBackground(amWidth, amHeight, Settings::ActivityMenu::backgroundColor);

	gui::TextArea noDateMsg("No date selected", Resources::arial, 35);

	activityMenu.setPosition(width * 2 / 3, Settings::MainWindow::padding.top)
		.setBackgroundTexture(Resources::ActivityMenu::background)
		.add("noDateSelectedMessage", noDateMsg.setPosition((amWidth - noDateMsg.getGlobalBounds().width) / 2, (amHeight - noDateMsg.getGlobalBounds().height) / 2));

}

void MainWindow::prepare()
{
	dateCalendar.prepare(calendarFrame);
	windowManager.emplace("dateCalendar", dateCalendar, true);
	windowManager.emplace("activityMenu", activityMenu, true);
}

void MainWindow::initialize()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "GIGA-Calendar", sf::Style::None);
	
	window.setVerticalSyncEnabled(true);

	/*
	SlideMonth slideDown(false, windowManager.at("dateCalendar", true));
	slideDown.setDuration(4).setFPS(20);
	*/
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.code != sf::Keyboard::Escape) break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				windowManager.input(event);
				break;
			}
		}

		window.clear(Settings::MainWindow::backgroundColor);
		window.draw(windowManager);
//		window.draw(slideDown);

		window.display();
	}
}
