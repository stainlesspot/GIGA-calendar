#include "DateCalendar.h"
 
DateCalendar::DateCalendar(gui::Window & w)
	: subWindow(&w)
{
}

DateCalendar & DateCalendar::setSubWindow(gui::Window &)
{
	subWindow
	return *this;
}
