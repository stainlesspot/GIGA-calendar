#include <time.h>
#include <iostream>
#include <chrono>


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
	
	const unsigned char fpsmCharSize = 16, windowMargin = 1;

	
	gui::WindowManager wm;

	sf::Texture t, t2;
	sf::Image i, i2;
	
	i.create((windowResolution.width - 2 * windowMargin) * 2 / 3, windowResolution.height - 2 * windowMargin, sf::Color::White);
	t.loadFromImage(i);

	wm.emplace("dateCalendar", gui::Window()
		.setBackgroundTexture(t)
		.setPosition(windowMargin, windowMargin)
		.setMovable(false), true);


	i2.create((windowResolution.width - 2 * windowMargin) / 3, windowResolution.height - 2 * windowMargin, sf::Color(40, 255, 40, 255));
	t2.loadFromImage(i2);
	wm.emplace("activityMenu", gui::Window()
		.setBackgroundTexture(t2)
		.setPosition((windowResolution.width - 2 * windowMargin) * 2 / 3 + windowMargin, windowMargin)
		.setMovable(false)
		.add("fpsMeter", gui::FPSMeter(fontArial, fpsmCharSize)
			.setPosition((windowResolution.width - 2 * windowMargin) / 3 - sf::Text("60", fontArial, fpsmCharSize).getGlobalBounds().width - 2 , 0)
			.setColor(sf::Color::Black)) , true);


	window.setFramerateLimit(60);

	char* array = new char[100];
	
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
		time_t today = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		ctime_s(array, 100, &today);
		std::cout << array;

		window.clear(sf::Color(150, 150, 150, 255));
		window.draw(wm);
		window.display();
	}

	return 0;
}
