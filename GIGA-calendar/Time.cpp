#include "Time.h"

Time::Time()
	: Time(0, 0, 0)
{}

Time::Time(const unsigned char hour, const unsigned char minute, const unsigned char second)
{
	setHour(hour);
	setMinute(minute);
	setSecond(second);
}

Time::Time(const unsigned long long seconds)
	: Time(seconds / 3600, (seconds - hour * 3600) / 60, seconds - hour * 3600 - minute * 60)
{
	setHour(seconds / 3600);
	setMinute((seconds - hour * 3600) / 60);
	setSecond(seconds - hour * 3600 - minute * 60);
}

const unsigned long long Time::asSeconds() const
{
	return hour * 3600 + minute * 60 + second;
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
	return Time(asSeconds() - seconds);
}

Time Time::operator-(const Time & t) const
{
	return Time(asSeconds() - t.asSeconds());
}

void Time::operator=(const unsigned long long seconds)
{
	setHour(seconds / 3600);
	setMinute((seconds - hour * 3600) / 60);
	setSecond(seconds - hour * 3600 - minute * 60);
}

Time & Time::operator=(const Time &t)
{
	setHour(t.hour);
	setMinute(t.minute);
	setSecond(t.second);
	return *this;
}

void Time::setHour(const unsigned char hour)
{
	this->hour = hour % 24;
}

void Time::setMinute(const unsigned char minute)
{
	this->minute = minute % 60;
}

void Time::setSecond(const unsigned char second)
{
	this->second = second % 60;
}

const unsigned char Time::getHour() const
{
	return hour;
}

const unsigned char Time::getMinute() const
{
	return minute;
}

const unsigned char Time::getSecond() const
{
	return second;
}
