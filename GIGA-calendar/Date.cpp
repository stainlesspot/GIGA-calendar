#include <chrono>
#include <iostream>

#include "Date.h"

const unsigned short Date::monthToDays[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
									//		  0   1   2   3   4    5    6    7    8    9    10   11   12

const bool Date::isLeapYear() const
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

Date::Date()
	: Date(1970, 1, 1)
{}

Date::Date(const unsigned short year, const uint8_t month, const uint8_t day, const bool beforeChrist)
	: year(year)
{
	setMonth(month);
	setDay(day);
}

Date::Date(unsigned long long days, const bool addUnixEpoch)
{

	if (addUnixEpoch)
		days += 719162;

	const unsigned int DAYS_IN_400_YEARS = 400 * 365 + 97;

	year = 400 * (days / DAYS_IN_400_YEARS);

	days %= DAYS_IN_400_YEARS;

	const unsigned int DAYS_IN_100_YEARS = 100 * 365 + 24;

	year += 100 * (days / DAYS_IN_100_YEARS);

	days %= DAYS_IN_100_YEARS;

	const unsigned int DAYS_IN_4_YEARS = 4 * 365 + 1;

	year += 4 * (days / DAYS_IN_4_YEARS);

	days %= DAYS_IN_4_YEARS;

	year += days / 365 + 1;

	days %= 365 + isLeapYear();

	month = 0;

	while (days >= monthToDays[month] + (isLeapYear() && month > 2))
		month++;

	day = days - monthToDays[month - 1] + 1;
}

Date Date::now()
{
	return Date(std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<24 * 3600>>>(std::chrono::system_clock::now().time_since_epoch()).count(), true);
}


const unsigned long long Date::asDays() const
{
	unsigned short cyear = year - 1;
	return cyear * 365 + cyear / 4 - cyear / 100 + cyear / 400 + monthToDays[month - 1] + (month > 2) + day;
}


Date Date::operator +(const long long days) const
{
	if (days < 0)
		return operator -(-days);
	else if (days == 0)
		return *this;
	return Date(asDays() + days);
}

Date Date::operator +(const Date & d) const
{
	return Date(asDays() + d.asDays());
}

Date Date::operator -(const long long days) const
{
	if (days < 0)
		return operator +(-days);
	else if (days == 0)
		return *this;
	return Date((asDays() > days) ? asDays() - days : days - asDays());
}

Date Date::operator -(const Date & d) const
{
	return Date((asDays() > d.asDays()) ? asDays() - d.asDays() : d.asDays() - asDays());
}

Date & Date::operator ++()
{
	operator =(*this + 1);
	return *this;
}

Date & Date::operator --()
{
	operator =(*this - 1);
	return *this;
}

bool Date::operator ==(const unsigned long long days) const
{
	return asDays() == days;
}

bool Date::operator ==(const Date & d) const
{
	return asDays() == d.asDays();
}

bool Date::operator !=(const unsigned long long days) const
{
	return !operator ==(days);
}

bool Date::operator !=(const Date & d) const
{
	return !operator ==(d);
}

bool Date::operator <(const unsigned long long days) const
{
	return asDays() < days;
}

bool Date::operator <(const Date & d) const
{
	return asDays() < d.asDays();
}

bool Date::operator <=(const unsigned long long days) const
{
	return operator <(days) || operator ==(days);
}

bool Date::operator <=(const Date & d) const
{
	return operator <=(d.asDays());
}

bool Date::operator >(const unsigned long long days) const
{
	return asDays() > days;
}

bool Date::operator >(const Date & d) const
{
	return asDays() > d.asDays();
}

bool Date::operator >=(const unsigned long long days) const
{
	return operator >(days) || operator ==(days);
}

bool Date::operator >=(const Date & d) const
{
	return operator >=(d.asDays());
}

void Date::operator =(const unsigned long long days)
{
	year = days == 0 ? 0 : 400 * (days / ((400.0f * 365.0f) + 97.0f));

	auto remDays = days - year * 365 - year / 4 + year / 100 - year / 400;
	month = 0;
	
	while (month < 12 && remDays > monthToDays[month] /*+ (month >= 2 ? (isLeapYear() ? 1 : 0) : 0)*/)
		month++;

	day = days ? (remDays - monthToDays[month - 1]) : 0;
}

Date & Date::setYear(const unsigned short year)
{
	this->year = year;
	return *this;
}

Date & Date::setMonth(const uint8_t month)
{
	this->month = month % 12;
	return *this;
}

Date & Date::setDay(const uint8_t day)
{
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		this->day = day % 31 != 0 ? day % 31 : 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		this->day = day % 30 != 0? day % 30 : 30;
		break;
	case 2:
		this->day = isLeapYear() ? (day % 29 ? day % 29 : 29) : (day % 28 ? day % 28 : 28);
		break;
	}
	return *this;
}

const unsigned short Date::getYear() const
{
	return year;
}

const uint8_t Date::getMonth() const
{
	return month;
}

const uint8_t Date::getDay() const
{
	return day;
}

const uint8_t Date::getDayOfWeek() const
{
	
	const unsigned int F = (14 - month) / 12,
	G = year - F,
	M = month + 12 * F - 2;
	return (day + G + (31 * M) / 12 + G / 4 - G / 100 + G / 400 - 1) % 7;
}

const uint8_t Date::getWeekNumber() const
{
	Date firstDay(year, 1, 1);
	uint8_t firstDayOfWeek = firstDay.getDayOfWeek();
	Date firstMonday(firstDay + 7 - firstDayOfWeek),
		thisMonday(*this - getDayOfWeek());

	if (*this < firstMonday)
		if (firstDayOfWeek < 4)
			return 1;
		else
			return thisMonday.getWeekNumber();

	return (thisMonday - firstMonday).asDays() / 7 + 1 + (firstDayOfWeek < 4);
}
