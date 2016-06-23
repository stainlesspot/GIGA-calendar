#pragma once

#include <string>
#include <memory>

#include "DateTime.h"

//	Event is an activity which is supposed to happen on a given date.
//	For example appointment at the doctor is an Event.
//	There could also be repetitive Events, which repeat after given time.
//	For example staff meetings in a company could be viewed as Events which repeat every month.
class Event {
	DateTime m_start;
	std::string m_name;
	std::unique_ptr<std::string> m_description;
	std::unique_ptr<DateTime> m_end, m_repetition;

public:
	Event(const DateTime& start, const std::string& name, std::unique_ptr<DateTime> end = nullptr, std::unique_ptr<std::string> description = nullptr, std::unique_ptr<DateTime> repetition = nullptr);
	
	Event() = default;
	Event(const Event&) = default;
	Event(Event&&) = default;
	~Event() = default;


	bool operator ==(const Event&) const;
	bool operator !=(const Event&) const;

	bool operator <(const Event&) const;
	bool operator <=(const Event&) const;

	bool operator >(const Event&) const;
	bool operator >=(const Event&) const;

	Event& operator =(const Event&) = default;
	Event& operator =(Event&&) = default;

	Event& setStart(const DateTime&);
	Event& setName(const std::string&);
	Event& setEnd(std::unique_ptr<DateTime>);
	Event& setDescription(std::unique_ptr<std::string>);
	Event& setRepetition(std::unique_ptr<DateTime>);

	const DateTime& getStart() const;
	const std::string& getName() const;
	std::unique_ptr<DateTime> getEnd() const;
	std::unique_ptr<std::string> getDescription() const;
	std::unique_ptr<DateTime> getRepetition() const;

	
};