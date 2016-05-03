#include <time.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <GUI/Button.h>
#include <GUI/WindowManager.h>
#include <GUI/FPSMeter.h>

#include "Calendar.h"



int main()
{
	sf::VideoMode windowResolution = sf::VideoMode::getDesktopMode();
	
	windowResolution.width = windowResolution.width * 2 / 3;
	windowResolution.height = windowResolution.height * 2 / 3;
	sf::RenderWindow window(windowResolution, "GIGA-Calendar", sf::Style::None);
	
	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");
	
	const unsigned char fpsmCharSize = 16, subWindowMargin = 20;
	gui::FPSMeter fpsMeter(fontArial, fpsmCharSize);
	fpsMeter.setPosition(windowResolution.width / 3 - 1.5 * fpsmCharSize, 0)
		.setColor(sf::Color::Black);

	gui::WindowManager wm;

	sf::Texture t, t2, t3;
	sf::Image i, i2, i3;
	
	i3.create(windowResolution.width, windowResolution.height, sf::Color(0, 0, 0, 0));
	t3.loadFromImage(i3);

	sf::RectangleShape border(sf::Vector2f(windowResolution.width, windowResolution.height));
	border.setOutlineThickness(-1);
	border.setOutlineColor(sf::Color(150, 150, 150, 255));
	border.setFillColor(sf::Color(255, 255, 255, 0));

	/*wm.emplace("border", gui::Window()
		.setBackgroundTexture(t3)
		.setPosition(0, 0)
		.setMovable(false), true);
		*/
	i.create((windowResolution.width * 2 / 3), windowResolution.height, sf::Color::White);
	t.loadFromImage(i);

	wm.emplace("dateCalendar", gui::Window()
		.setBackgroundTexture(t)
		.setPosition(0, 0)
		.setMovable(false), true);
	
	i2.create(windowResolution.width / 3 + 1, windowResolution.height, sf::Color(40, 255, 40, 255));
	t2.loadFromImage(i2);
	wm.emplace("activityMenu", gui::Window()
		.setBackgroundTexture(t2)
		.setPosition(windowResolution.width * 2 / 3 , 0)
		.setMovable(false)
		.add("fpsMeter", fpsMeter), true);


	window.setFramerateLimit(60);
	
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
				wm.input(event);
				break;
			}
		}
		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(wm);
		window.display();
	}

	return 0;
}
