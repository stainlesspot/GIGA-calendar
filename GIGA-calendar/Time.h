#pragma once
class Time {
private:
	unsigned char hour;
	unsigned char minute;
	unsigned char second;

public:
	Time();
	Time(const unsigned char hour, const unsigned char minute, const unsigned char second);
	Time(const unsigned long long seconds);

	Time operator +(const unsigned long long seconds) const;
	Time operator +(const Time&) const;

	Time operator -(const unsigned long long seconds) const;
	Time operator -(const Time&) const;

	Time& operator =(const Time&);


};