#include <chrono>
#include <iostream>
#include <algorithm>

#include "Date.h"

const unsigned short Date::monthToDays[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
									//		  0   1   2   3   4    5    6    7    8    9    10   11   12

const bool Date::isLeapYear() const
{
	return (m_year % 4 == 0 && m_year % 100 != 0) || m_year % 400 == 0;
}
const uint8_t Date::getMaxDay() const{
	switch (m_month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 2:
		return isLeapYear() ? 29 : 28;
	default:
		return 30;
	}
}

Date::Date()
	: Date(1970, 1, 1)
{}

Date::Date(const unsigned short year, const uint8_t month, const uint8_t day)
	: m_year(year)
{
	setMonth(month);
	setDay(day);
}

Date::Date(unsigned long long days, const bool addUnixEpoch)
{

	if (addUnixEpoch)
		days += 719162;

	const unsigned int DAYS_IN_400_YEARS = 400 * 365 + 97;

	m_year = 400 * (days / DAYS_IN_400_YEARS);

	days %= DAYS_IN_400_YEARS;

	const unsigned int DAYS_IN_100_YEARS = 100 * 365 + 24;

	m_year += 100 * (days / DAYS_IN_100_YEARS);

	days %= DAYS_IN_100_YEARS;

	const unsigned int DAYS_IN_4_YEARS = 4 * 365 + 1;

	m_year += 4 * (days / DAYS_IN_4_YEARS);

	days %= DAYS_IN_4_YEARS;

	m_year += days / 365 + 1;

	days %= 365;

	m_month = 0;

	while (days >= monthToDays[m_month] + (isLeapYear() && m_month > 2))
		m_month++;

	m_day = days - monthToDays[m_month - 1] + !(isLeapYear() && m_month > 2);
}

Date Date::now()
{
	return Date(std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<24 * 3600>>>(std::chrono::system_clock::now().time_since_epoch()).count(), true);
}


const unsigned long long Date::asDays() const
{
	const unsigned short cyear = m_year - 1;
	return cyear * 365 + cyear / 4 - cyear / 100 + cyear / 400 + monthToDays[m_month - 1] + m_day - !(isLeapYear() && m_month > 2);
}

const std::string Date::asString(const std::string& format) const
{
	const std::string monthToWord[13] = {
		"0",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	std::string returnValue;

	bool escape = false;

	for (auto it = format.begin(), end = format.end(); it != end; it++) {

		if (escape) {
			returnValue += *it;
			escape = false;
			continue;
		}
		
		switch (*it) {
		case 'D':
			if (m_day < 10)
				returnValue += '0';
		case 'd':
			returnValue += std::to_string(m_day);
			break;
		case 'm':
			returnValue += std::to_string(m_month);
			break;
		case 'M':
			returnValue += monthToWord[m_month];
			break;
		case 'Y':
			if (m_year / 100 != 0)
				returnValue += std::to_string(m_year / 100);
		case 'y':
			returnValue += std::to_string(m_year % 100);
			break;
		case '\\':
			escape = true;
			break;
		default:
			returnValue += *it;
		}
	}
	return returnValue;
}

Date & Date::addMonths(const int numberOfMonths)
{
	m_year += numberOfMonths / 12;

	int temp = m_month + numberOfMonths % 12;

	if (temp > 12) {
		m_year++;
		m_month = temp % 12 ? temp % 12 : 12;
	}
	else if (temp < 1) {
		m_year--;
		m_month = 12 + numberOfMonths % 12 + m_month;
	}
	else
		m_month = temp;

	return *this;
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
	++m_day;
	if (m_day > getMaxDay()) {
		m_day = 1;
		++m_month;
		if (m_month > 12) {
			m_month = 1;
			++m_year;
		}
	}
	return *this;
}

Date & Date::operator --()
{
	if (m_day == 1) {
		if (m_month == 1) {
			--m_year;
			m_month = 12;
		}
		else
			--m_month;
		m_day = getMaxDay();
	}
	else
		--m_day;
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

void Date::operator =(unsigned long long days)
{
	const unsigned int DAYS_IN_400_YEARS = 400 * 365 + 97;

	m_year = 400 * (days / DAYS_IN_400_YEARS);

	days %= DAYS_IN_400_YEARS;

	const unsigned int DAYS_IN_100_YEARS = 100 * 365 + 24;

	m_year += 100 * (days / DAYS_IN_100_YEARS);

	days %= DAYS_IN_100_YEARS;

	const unsigned int DAYS_IN_4_YEARS = 4 * 365 + 1;

	m_year += 4 * (days / DAYS_IN_4_YEARS);

	days %= DAYS_IN_4_YEARS;

	m_year += days / 365 + 1;

	days %= 365;

	m_month = 0;

	while (days >= monthToDays[m_month] + (isLeapYear() && m_month > 2))
		m_month++;

	m_day = days - monthToDays[m_month - 1] + !(isLeapYear() && m_month > 2);
}

Date & Date::setYear(const unsigned short year)
{
	m_year = year;
	return *this;
}

Date & Date::setMonth(const uint8_t month)
{
	m_month = month % 12 ? month % 12 : 12;
	return *this;
}

Date & Date::setDay(const uint8_t day)
{
	switch (m_month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		m_day = (day % 31) ? day % 31 : 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		m_day = (day % 30) ? day % 30 : 30;
		break;
	case 2:
		m_day = isLeapYear() ? ((day % 29) ? day % 29 : 29) : ((day % 28) ? day % 28 : 28);
		break;
	default:
		m_day = 30;
		break;
	}
	return *this;
}

const unsigned short Date::getYear() const
{
	return m_year;
}

const uint8_t Date::getMonth() const
{
	return m_month;
}

const uint8_t Date::getDay() const
{
	return m_day;
}

const Date Date::getMonday() const
{
	return Date(*this - getDayOfWeek());
}

const uint8_t Date::getDayOfWeek() const
{
	
	const unsigned int F = (14 - m_month) / 12,
	G = m_year - F,
	M = m_month + 12 * F - 2;
	return (m_day + G + (31 * M) / 12 + G / 4 - G / 100 + G / 400 - 1) % 7;
}

const uint8_t Date::getWeekNumber() const
{
	Date firstDay(m_year, 1, 1);
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
