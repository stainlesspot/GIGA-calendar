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

	const unsigned long long asSeconds() const;

	Time operator +(const unsigned long long seconds) const;
	Time operator +(const Time&) const;

	Time operator -(const unsigned long long seconds) const;
	Time operator -(const Time&) const;

	void operator =(const unsigned long long seconds);
	Time& operator =(const Time&);

	void setHour(const unsigned char hour);
	void setMinute(const unsigned char minute);
	void setSecond(const unsigned char second);

	const unsigned char getHour() const;
	const unsigned char getMinute() const;
	const unsigned char getSecond() const;
};