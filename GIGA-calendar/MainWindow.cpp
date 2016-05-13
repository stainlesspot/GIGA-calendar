#include "MainWindow.h"


MainWindow::MainWindow()
	: width(sf::VideoMode::getDesktopMode().width * 2 / 3), height(sf::VideoMode::getDesktopMode().height * 2 / 3),
	windowMargin(1), leftSide(sf::Vector2f(windowMargin, windowMargin), (width - 2 * windowMargin) * 2 / 3,
		height - 2 * windowMargin, sf::Color(255, 255, 255, 255)), rightSide()
{

}

void MainWindow::prepare()
{

}
