
#include <SFML/Graphics.hpp>

#include <GUI/Gui.h>

#include "MainWindow.h"
#include "Resources.h"

void main() {

	Resources::load();
	MainWindow mainWindow;
	mainWindow.initialize();
}

