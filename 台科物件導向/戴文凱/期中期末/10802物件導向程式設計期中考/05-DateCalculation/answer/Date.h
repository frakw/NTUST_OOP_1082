#ifndef DATE_H
#define DATE_H

#define YEAR_LIMIT 2020

class Date
{
public:
	int m_year, m_month, m_day;

	Date(int y, int m, int d) : m_year(y), m_month(m), m_day(d) {}
	~Date() {}
	bool check();
	friend bool operator> (const Date& date1, const Date& date2);
	friend bool operator< (const Date& date1, const Date& date2);
	friend int operator- (const Date& date1, const Date& date2);
	Date operator- (const int num);
	Date operator+ (const int num);
	friend Date operator+ (const int num, const Date& date);

private:

};

#endif