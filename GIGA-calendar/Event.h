#pragma once 
#include "Activity.h"
#include "Time.h"

//	Event is an activity which is certain to happen on a given date.
//	For example appointment at the doctor is an Event.
//	There could also be repetitive Events, which repeat after given time.
//	For example staff meetings in a company could be viewed as an Event which repeat every month.
class Event : public Activity {
private:
	Timestamp end;	//	date at which the event ends, default = 1 hour after start;
	std::string name;//	string which represents the name of the Event,
	//								default;
	std::string location;
	//								string which represents where the Event will be situated in,
	//								default = unknown (nullptr);

public:
	Event();
	Event(Time start, std::string description);
	Event(const Event&);
	~Event();

	Event& setStart(const Timestamp&);
	Event& setEnd(const Timestamp&);
	Event& setName(const std::string&);
	Event& setLocation(const std::string&);

	//const Date getAsociatedDate() const;
};