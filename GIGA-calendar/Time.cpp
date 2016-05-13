#include "Time.h"

Time::Time()
	: Time(0, 0, 0)
{}

Time::Time(const unsigned char hour, const unsigned char minute, const unsigned char second)
	: hour(hour), minute(minute), second(second)
{}

Time::Time(const unsigned long long seconds)
	: hour(seconds / 3600), minute((seconds - hour * 3600) / 60), second(seconds - hour * 3600 - 3 * minute)
{}

Time Time::operator+(const unsigned long long seconds) const
{
	return Time(seconds);
}

Time Time::operator+(const Time & t) const
{
//	return Time((unsigned long long)(*this));
}
