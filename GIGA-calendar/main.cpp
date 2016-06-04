#include <time.h>
#include <iostream>
#include <chrono>


#include <SFML/Graphics.hpp>

#include <GUI/Gui.h>

#include "MainWindow.h"
#include "Resources.h"

/*#include "Calendar.h"
#include "DateTime.h"




void main()
{
	sf::VideoMode windowResolution = sf::VideoMode::getDesktopMode();
	
	windowResolution.width = windowResolution.width * 2 / 3;
	windowResolution.height = windowResolution.height * 2 / 3;
	sf::RenderWindow window(windowResolution, "GIGA-Calendar", sf::Style::None);
	
	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");

	const uint8_t fpsmCharSize = 16, textCharSize = 20, windowMargin = 1;
	
	gui::WindowManager wm;

	sf::Texture t, t2;
	sf::Image i, i2;
	

	i.create((windowResolution.width - 2 * windowMargin) * 2 / 3, windowResolution.height - 2 * windowMargin, sf::Color::White);
	t.loadFromImage(i);


	Time tim(7655);

	//gui::Button().


	wm.emplace("dateCalendar", gui::Window()
		.setBackgroundTexture(t)
		.setPosition(windowMargin, windowMargin)
		.setMovable(false)

		.add("timeTextArea", gui::TextArea("Time tim: " + std::to_string(tim.getHour()) + ':' + std::to_string(tim.getMinute()) + ':' + std::to_string(tim.getSecond()) + "\n", fontArial, textCharSize)
			.setPosition(2, 0)
			.setUpdateFunction([]()
			{
				//Time timati = Time::now();
				//Date doni = Date::now();
				DateTime doni(DateTime::now());

				return gui::bind("Current time - " + std::to_string(doni.getHour()) + ':' + std::to_string(doni.getMinute()) + ':' + std::to_string(doni.getSecond()) + '\n' +
					"Current date: " + std::to_string(doni.getYear()) + '-' + std::to_string(doni.getMonth()) + '-' + std::to_string(doni.getDay()) + '\n'
					,sf::Color::Black);
			})
			.setColor(sf::Color::Black)),true);

//	gui::Duration;
//	gui::Internals::timeSinceStart(); 
	


	i2.create((windowResolution.width - 2 * windowMargin) / 3, windowResolution.height - 2 * windowMargin, sf::Color(40, 255, 40, 255));
	t2.loadFromImage(i2);
	//t2.loadFromFile("grass.png");
	
	wm.emplace("activityMenu", gui::Window()
		.setBackgroundTexture(t2)
		.setPosition((windowResolution.width - 2 * windowMargin) * 2 / 3 + windowMargin, windowMargin)
		.setMovable(false)
		.add("fpsMeter", gui::FPSMeter(fontArial, fpsmCharSize)
			.setPosition((windowResolution.width - 2 * windowMargin) / 3 - sf::Text("60", fontArial, fpsmCharSize).getGlobalBounds().width - 2 , 0)
			.setColor(sf::Color::Black)) , true);


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

		window.clear(sf::Color(150, 150, 150, 255));
		window.draw(wm);
		window.display();
	}
}*/


void main() {
	Resources::load();
	MainWindow mainWindow;
	mainWindow.initialize();
}

