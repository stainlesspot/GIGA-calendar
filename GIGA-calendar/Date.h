#pragma once
class Date {
private:
	unsigned char day;
	unsigned char month;
	unsigned short year;

public:
	Date();
	Date(const unsigned char day, const unsigned char month, const unsigned short year);
	Date(const unsigned long long days);
	//~Date();

	/*virtual*/ bool isValid();
	//	if month is [1,3,5,7,8,10 or 12], maxDay is 31;
	//	if month is [4,6,9 or 11], maxDay is 30;
	//	if month is 2 and year is leap, maxDay is 29;
	//	if month is 2 and year is not leap, maxDay is 28.

	virtual const Date operator +(const Date&) const;// (?)
	virtual const Date operator -(const Date&) const;
	virtual Date& operator =(const Date&);
};