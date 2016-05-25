#include <chrono>

#include "DateTime.h"

DateTime::DateTime()
	: DateTime(1970, 1, 1, 0, 0, 0)
{}

DateTime::DateTime(const unsigned short year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t minute, const uint8_t second)
	: Date(year, month, day), Time(hour, minute, second)
{}

DateTime::DateTime(const unsigned long long seconds, const bool addUTCEpoch)
	: Date(seconds / (24 * 3600), addUTCEpoch), Time(seconds % (24 * 3600))
{}

DateTime DateTime::now()
{
	return DateTime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), true);
}

const unsigned long long DateTime::asSeconds() const
{
	return asDays() * 24 * 3600 + Time::asSeconds();
}

DateTime DateTime::operator+(const unsigned long long seconds) const
{
	return DateTime(asSeconds() + seconds);
}

DateTime DateTime::operator+(const DateTime & dt) const
{
	return DateTime(asSeconds() + dt.asSeconds());
}

DateTime DateTime::operator-(const unsigned long long seconds) const
{
	return DateTime(asSeconds() > seconds ? asSeconds() - seconds : seconds - asSeconds());
}

DateTime DateTime::operator-(const DateTime & dt) const
{
	return DateTime(asSeconds() > dt.asSeconds() ? asSeconds() - dt.asSeconds() : dt.asSeconds() - asSeconds());
}

void DateTime::operator=(const unsigned long long seconds)
{
	Date::operator=(seconds / (24 * 3600));
	Time::operator=(seconds % (24 * 3600));
}

