#pragma once

#include <cstdint>

class Time {
private:
	uint8_t hour;
	uint8_t minute;
	uint8_t second;

public:
	Time();
	Time(const uint8_t hour, const uint8_t minute, const uint8_t second);
	Time(const unsigned long long seconds);

	Time(const Time&) = default;
	Time(Time&&) = default;
	virtual ~Time() = default;

	static Time now();

	virtual const unsigned long long asSeconds() const;

	Time operator +(const unsigned long long seconds) const;
	Time operator +(const Time&) const;

	Time operator -(const unsigned long long seconds) const;
	Time operator -(const Time&) const;

	void operator =(const unsigned long long seconds);

	Time& operator =(const Time&) = default;
	Time& operator =(Time&&) = default;

	Time& setHour(const uint8_t hour);
	Time& setMinute(const uint8_t minute);
	Time& setSecond(const uint8_t second);

	const uint8_t getHour() const;
	const uint8_t getMinute() const;
	const uint8_t getSecond() const;
};