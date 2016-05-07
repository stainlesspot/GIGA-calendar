#pragma once

#include <SFML/Graphics.hpp>

#include <GUI/GUI.h>

class MainWindow {
private:
	gui::WindowManager subwindowManager;
	sf::VideoMode windowVMode;


public:
	MainWindow();

	void loadFrom(std::string filename);
	void saveTo(std::string filename);

	void prepare();
	void initialize();

};