#include "DateCalendar.h"
 
DateCalendar::DateCalendar(gui::WindowManager & wm)
{
	subWindow = &wm.at("dateCalendar", true);
}
