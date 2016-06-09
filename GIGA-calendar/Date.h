#pragma once

#include <cstdint>

/*enum Month
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};*/

class Date {
private:

	uint8_t day;
	uint8_t month;
	short year;

	static const unsigned short monthToDays[13];

	const bool isLeapYear() const;

public:
	Date();
	Date(const unsigned short year, const uint8_t month, const uint8_t day, const bool beforeChrist = false);
	Date(unsigned long long days, const bool addUnixEpoch = false);

	Date(const Date&) = default;
	Date(Date&&) = default;
	virtual ~Date() = default;

	static Date now();

	const unsigned long long asDays() const;

	const std::string asString() const;

	Date operator +(const long long days) const;
	Date operator +(const Date&) const; // Duration
	
	Date operator -(const long long days) const;
	Date operator -(const Date&) const; // Duration

	Date& operator ++();

	Date& operator --();

	bool operator ==(const unsigned long long days) const;
	bool operator ==(const Date&) const;

	bool operator !=(const unsigned long long days) const;
	bool operator !=(const Date&) const;

	bool operator <(const unsigned long long days) const;
	bool operator <(const Date&) const;
	
	bool operator <=(const unsigned long long days) const;
	bool operator <=(const Date&) const;
	
	bool operator >(const unsigned long long days) const;
	bool operator >(const Date&) const;

	bool operator >=(const unsigned long long days) const;
	bool operator >=(const Date&) const;

	void operator =(const unsigned long long days);

	Date& operator =(const Date&) = default;
	Date& operator =(Date&&) = default;

	Date& setYear(const unsigned short year);
	Date& setMonth(const uint8_t month);
	Date& setDay(const uint8_t day);

	const unsigned short getYear() const;
	const uint8_t getMonth() const;
	const uint8_t getDay() const;

	const uint8_t getDayOfWeek() const;
	const uint8_t getWeekNumber() const;



};