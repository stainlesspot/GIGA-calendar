#pragma once

#include <GUI/GUI.h>

class SlideMonth : public gui::Animation{
private:
	bool upwards;
	gui::Window& window;

	void step() const;


public:
	SlideMonth(bool upwards, gui::Window& window);

	SlideMonth() = default;
	SlideMonth(const SlideMonth&) = default;
	SlideMonth(SlideMonth&&) = default;
	~SlideMonth() = default;

	SlideMonth& operator =(const SlideMonth&) = default;
	SlideMonth& operator =(SlideMonth&&) = default;
};