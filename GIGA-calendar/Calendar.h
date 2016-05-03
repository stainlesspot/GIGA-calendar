#pragma once

#include <SFML/Graphics.hpp>

#include <GUI/WindowManager.h>

class Calendar : public sf::Drawable {
private:
	gui::WindowManager main;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;

public:
	Calendar() = default;
	Calendar(const Calendar&) = default;
	Calendar(const sf::VideoMode&);


	Calendar& prepare();


};