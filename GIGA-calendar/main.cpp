
#include <SFML/Graphics.hpp>

#include <GUI/Gui.h>

#include "MainWindow.h"
#include "Resources.h"
#include "Settings.h"

void main() {
	Settings::loadFromFile("config.ini");
	Resources::load();
	MainWindow mainWindow;
	mainWindow.initialize();
}

