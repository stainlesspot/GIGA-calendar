#pragma once

#include <GUI\GUI.h>

class Subwindow {
private:
	gui::Window window;

public:
	virtual Subwindow& prepare() = 0;

	void addTo(const gui::WindowManager&);
};