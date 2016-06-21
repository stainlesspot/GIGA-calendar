#include "Event.h"

Event::Event(const DateTime & start, const std::string & name, const std::unique_ptr<DateTime>& end, const std::unique_ptr<std::string>& description, const std::unique_ptr<DateTime>& repetition)
	: m_start(start), m_name(name), m_end(*end), m_description(*description), m_repetition(*repetition)
{}

bool Event::operator==(const Event & e) const
{
	return m_start == e.m_start && m_name == e.m_name &&;
}

Event & Event::setStart(const DateTime & dt)
{
	m_start = dt;
	return *this;
}

Event & Event::setName(const std::string & s)
{
	m_name = s;
	return *this;
}

Event & Event::setEnd(const std::unique_ptr<DateTime>& dt)
{
	m_end.reset(dt.get());
	return *this;
}

Event & Event::setDescription(const std::unique_ptr<std::string>& s)
{
	m_description.reset(s.get());
	return *this;
}

Event & Event::setRepetition(const std::unique_ptr<DateTime>& dt)
{
	m_repetition.reset(dt.get());
	return *this;
}

const DateTime& Event::getStart() const
{
	return m_start;
}

const std::string & Event::getName() const
{
	return m_name;
}

const std::unique_ptr<DateTime>& Event::getEnd() const
{
	return m_end;
}

const std::unique_ptr<std::string>& Event::getDescription() const
{
	return m_description;
}

const std::unique_ptr<DateTime>& Event::getRepetition() const
{
	return m_repetition;
}
