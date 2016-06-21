#include "Event.h"

Event::Event(const DateTime & start, const std::string & name, std::unique_ptr<DateTime> end, std::unique_ptr<std::string> description, std::unique_ptr<DateTime> repetition)
	: m_start(start), m_name(name), m_end(std::move(end)), m_description(std::move(description)), m_repetition(std::move(repetition))
{}

bool Event::operator==(const Event & e) const
{
	return m_start == e.m_start && m_name == e.m_name;
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

Event & Event::setEnd(std::unique_ptr<DateTime> dt)
{
	m_end = std::move(dt);
	return *this;
}

Event & Event::setDescription(std::unique_ptr<std::string> s)
{
	m_description = std::move(s);
	return *this;
}

Event & Event::setRepetition(std::unique_ptr<DateTime> dt)
{
	m_repetition = std::move(dt);
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


std::unique_ptr<DateTime> Event::getEnd() const
{
	return std::unique_ptr<DateTime>(m_end.get());
}

std::unique_ptr<std::string> Event::getDescription() const
{
	return std::unique_ptr<std::string>(m_description.get());
}

std::unique_ptr<DateTime> Event::getRepetition() const
{
	return std::unique_ptr<DateTime>(m_repetition.get());
}
