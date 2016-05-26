#include "MainWindow.h"
#include "Settings.h"


MainWindow::MainWindow()
	: width(sf::VideoMode::getDesktopMode().width * 2 / 3), height(sf::VideoMode::getDesktopMode().height * 2 / 3),
	dateCalendar(sf::Vector2f(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top), (width - Settings::MainWindow::padding.left - Settings::MainWindow::padding.right ) * 2 / 3,
		height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom), activityMenu()
{}

void MainWindow::prepare()
{
	dateCalendar.prepare();
	windowManager.emplace("dateCalendar", dateCalendar, true);

}

void MainWindow::initialize()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "GIGA-Calendar", sf::Style::None);
	
	window.setVerticalSyncEnabled(true);

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
		window.display();
	}
}
