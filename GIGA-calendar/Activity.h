#pragma once
#include <string>
//#include "Structs.h"
#include "DateTime.h"

//	This is a base class, which represents what fields and methods
//	Event and Task classes have in common.
class Activity {
private:
	std::string name;
	std::unique_ptr<std::string> description;
	std::unique_ptr<DateTime> repetition;

public:
	Activity();
	Activity(const std::string& description, const std::unique_ptr<std::string>, const std::unique_ptr<DateTime>);
	
	Activity(const Activity&) = default;
	Activity(Activity&&) = default;
	virtual ~Activity() = default;


	Activity& setName(const std::string&);
	Activity& setDescription(const std::unique_ptr<std::string>);
	Activity& setRepetition(const std::unique_ptr<DateTime>);

	std::string getName() const;
	std::unique_ptr<std::string> getDescription() const;
	std::unique_ptr<DateTime> getRepetition() const;

	Activity& operator =(const Activity&) = default;
	Activity& operator =(Activity&&) = default;

};