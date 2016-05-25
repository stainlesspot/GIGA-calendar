#include "MainWindow.h"
#include "Settings.h"


MainWindow::MainWindow()
	: width(sf::VideoMode::getDesktopMode().width * 2 / 3), height(sf::VideoMode::getDesktopMode().height * 2 / 3),
	leftSide(sf::Vector2f(Settings::mainWindowPadding, Settings::mainWindowPadding), (width - 2 * Settings::mainWindowPadding) * 2 / 3,
		height - 2 * Settings::mainWindowPadding), rightSide()
{}

void MainWindow::prepare()
{
	leftSide.prepare();
	windowManager.emplace("dateCalendar", leftSide, true);

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

		window.clear(Settings::mainWindowBackgroundColor);
		window.draw(windowManager);
		window.display();
	}
}
