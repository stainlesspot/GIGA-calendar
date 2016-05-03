#include "Structs.h"

Date::Date()
	:Date(1, 1, 1990)
{
}

Date::Date(unsigned char day, unsigned char month, unsigned short year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::Date(const Date & d)
	:Date(d.day, d.month, d.year)
{
}

Timestamp::Timestamp()
	:Timestamp(1, 1, 1990, 0, 0, 0)
{
}

Timestamp::Timestamp(unsigned char day, unsigned char month, unsigned short year,
						unsigned char hours, unsigned char minutes, unsigned char seconds)
	:Date(day, month, year)
{
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

Timestamp::Timestamp(const Timestamp &t)
	:Timestamp(t.day, t.month, t.year, t.hours, t.minutes, t.seconds)
{
}
