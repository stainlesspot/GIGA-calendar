#pragma once
class Time {
private:
	unsigned char hour;
	unsigned char minute;

public:
	Time();
	Time(const unsigned char hour, const unsigned char minute);
	Time(const unsigned long long minutes);

	virtual const Time operator +(const Time&) const;
	virtual const Time operator -(const Time&) const;
	virtual Time& operator =(const Time&);


};