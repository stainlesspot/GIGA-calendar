#pragma once
struct Point {
	int x;
	int y;
	Point() 
		:Point(0, 0) {}
	Point(const int x, const int y) {
		this->x = x;
		this->y = y;
	}
	Point(const Point& p)
		:Point(p.x, p.y) {}
};
struct Date {
	unsigned char day;//	ranges from 1 to 31
	unsigned char month;//	ranges from 1 to 12
	unsigned short year;//	ranges from 1 to 9999
	
	Date();
	Date(const unsigned char day, const unsigned char month, const unsigned short year);
	Date(const Date&);

	virtual Date operator -(const Date&);
	virtual Date operator +(const Date&);
	Date& operator ++();

};
struct Timestamp : public Date{
	unsigned char hour;//		ranges from 0 to 23
	unsigned char minute;//	ranges from 0 to 59
	Timestamp();
	Timestamp(const unsigned long long minutes);
	Timestamp(const Timestamp&);

	Timestamp operator +=(const unsigned long long minutes);
};
struct Color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	Color();
	Color(const unsigned char red, const unsigned char green, const unsigned char blue);
	Color(const Color&);

};