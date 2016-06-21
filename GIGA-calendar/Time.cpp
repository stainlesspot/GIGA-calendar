#include <chrono>
#include <iostream>

#include "Time.h"

Time::Time()
	: Time(0, 0, 0)
{}

Time::Time(const uint8_t hour, const uint8_t minute, const uint8_t second)
{
	setHour(hour);
	setMinute(minute);
	setSecond(second);
}

Time::Time(const unsigned long long seconds)
{
	setHour(seconds % (24 * 3600) / 3600);
	setMinute((seconds % 3600) / 60);
	setSecond(seconds % 60);
}

Time Time::now()
{
	return Time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}

const unsigned long long Time::asSeconds() const
{
	return m_hour * 3600 + m_minute * 60 + m_second;
}

Time Time::operator+(const unsigned long long seconds) const
{
	return Time(asSeconds() + seconds);
}

Time Time::operator+(const Time & t) const
{
	return Time(asSeconds() + t.asSeconds());
}

Time Time::operator-(const unsigned long long seconds) const
{
	return Time(asSeconds() > seconds ? asSeconds() - seconds : seconds - asSeconds());
}

Time Time::operator-(const Time & t) const
{
	return Time(asSeconds() > t.asSeconds() ? asSeconds() - t.asSeconds() : t.asSeconds() - asSeconds());
}

bool Time::operator==(const unsigned long long seconds) const
{
	return asSeconds() == seconds;
}

bool Time::operator==(const Time & t) const
{
	return m_second == t.m_second  && m_minute == t.m_minute && m_hour == t.m_hour;
}

bool Time::operator!=(const unsigned long long seconds) const
{
	return !operator ==(seconds);
}

bool Time::operator!=(const Time & t) const
{
	return !operator ==(t);
}

bool Time::operator<(const unsigned long long seconds) const
{
	return asSeconds() < seconds;
}

bool Time::operator<(const Time & t) const
{
	return operator <(t.asSeconds());
}

bool Time::operator<=(const unsigned long long seconds) const
{
	return asSeconds() <= seconds;
}

bool Time::operator<=(const Time & t) const
{
	return operator <=(t.asSeconds());
}

bool Time::operator>(const unsigned long long seconds) const
{
	return asSeconds() > seconds;
}

bool Time::operator>(const Time & t) const
{
	return operator >(t);
}

bool Time::operator>=(const unsigned long long seconds) const
{
	return asSeconds() >= seconds;
}

bool Time::operator>=(const Time & t) const
{
	return operator >=(t.asSeconds());
}

void Time::operator=(const unsigned long long seconds)
{
	setHour(seconds % (24 * 3600) / 3600);
	setMinute((seconds % 3600) / 60);
	setSecond(seconds % 60);
}

Time& Time::setHour(const uint8_t hour)
{
	m_hour = hour % 24;
	return *this;
}

Time& Time::setMinute(const uint8_t minute)
{
	m_minute = minute % 60;
	return *this;
}

Time& Time::setSecond(const uint8_t second)
{
	m_second = second % 60;
	return *this;
}

const uint8_t Time::getHour() const
{
	return m_hour;
}

const uint8_t Time::getMinute() const
{
	return m_minute;
}

const uint8_t Time::getSecond() const
{
	return m_second;
}
