#pragma once

#include <string>
//#include <optional>

#include "DateTime.h"

//	Event is an activity which is supposed to happen on a given date.
//	For example appointment at the doctor is an Event.
//	There could also be repetitive Events, which repeat after given time.
//	For example staff meetings in a company could be viewed as an Event which repeat every month.
class Event {
private:
	DateTime start, end;
	std::string name, description;
//	std::optional<DateTime> repetition; 

public:
	Event();
	Event(const DateTime& start, const DateTime& end, const std::string& name, const std::string& description);
	
	Event(const Event&) = default;
	Event(Event&&) = default;
	~Event() = default;

	Event& setStart(const DateTime&);
	Event& setEnd(const DateTime&);
	Event& setName(const std::string&);
	Event& setLocation(const std::string&);

	DateTime getStart();
	DateTime getEnd();
	std::string getName();
	std::string getDescription();

	Event& operator =(const Event&) = default;
	Event& operator =(Event&&) = default;

};