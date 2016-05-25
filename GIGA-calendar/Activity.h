#pragma once
#include <string>
//#include "Structs.h"
#include "Time.h"

//	This is a base class, which represents what fields and methods
//	Event and Task classes have in common.
class Activity {
private:
	Time asociatedTime;
	//	the defining time of the derived classes, it is shown to the user at vertical view.
	//	for Event it is start time, for Task - deadline.
	std::string description;
//	Timestamp* repetition = nullptr;
	//	the time period which, when elapsed, the Activity repeats,
	//	Activities which do not repeat have this field set to nullptr,
	//	default = no repeat(nullptr);
public:
	Activity();
	Activity(std::string* description);
	virtual ~Activity();

	Activity& setDescription(const std::string&);
//	Activity& setRepetition(const Timestamp&);

	virtual Activity& operator =(const Activity*);
	virtual const Time getAsociatedTime() const;
};