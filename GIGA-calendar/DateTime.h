#pragma once

#include "Date.h"
#include "Time.h"

class DateTime : public Date, public Time {
public:
	DateTime();
	DateTime(const unsigned short year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t minute, const uint8_t second);
	DateTime(const unsigned long long seconds, const bool addUTCEpoch =  false);

	DateTime(const DateTime&) = default;
	DateTime(DateTime&&) = default;
	~DateTime() = default;

	static DateTime now();

	const unsigned long long asSeconds() const;

	bool operator ==(const unsigned long long seconds) const;
	bool operator ==(const DateTime&) const;

	bool operator != (const unsigned long long seconds) const;
	bool operator != (const DateTime&) const;

	bool operator < (const unsigned long long seconds) const;
	bool operator < (const DateTime&) const;

	bool operator <= (const unsigned long long seconds) const;
	bool operator <= (const DateTime&) const;

	bool operator > (const unsigned long long seconds) const;
	bool operator > (const DateTime&) const;

	bool operator >= (const unsigned long long seconds) const;
	bool operator >= (const DateTime&) const;

	
	DateTime operator +(const unsigned long long seconds) const;
	DateTime operator +(const DateTime&) const;

	DateTime operator -(const unsigned long long seconds) const;
	DateTime operator -(const DateTime&) const;

	void operator =(const unsigned long long seconds);

	DateTime& operator =(const DateTime&) = default;
	DateTime& operator =(DateTime&&) = default;

};